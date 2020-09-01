#include "qc.h"
#include "string.h"

#define DEFAULT_ALLOC_SIZE 4
enum {
    OPT_FLAG,
    OPT_UNSIGNED,
    OPT_SIGNED,
    OPT_DOUBLE,
    OPT_STRING,
};

struct short_flag {
    char name;
    char* hint;
    bool* dst;
};

struct long_opt {
    char* name;
    char* hint;
    int type;
    bool mandatory;
    bool provided;
    union {
        size_t unsigned_default;
        ptrdiff_t signed_default;
        double double_default;
        char* string_default;
    } default_value;
    union {
        bool* flag_ptr;
        size_t* unsigned_ptr;
        ptrdiff_t* signed_ptr;
        double* double_ptr;
        char** string_ptr;
    } dst;
};

struct qc_args {
    struct short_flag* flags;
    size_t flags_count;
    size_t flags_capacity;
    struct long_opt* opts;
    size_t opts_count;
    size_t opts_capacity;
    char* program_name;
    void (*help) (void*);
    void* help_data;
    int positionals_index;
    int positionals_count;
    int extras_index;
    int extras_count;
    bool parsed;
};

__QC_NORETURN static void call_help(qc_args* args);
static void auto_help(qc_args* args);
static void array_push_back(void** array, size_t* count, size_t* capacity, size_t size);
static void add_long_opt(qc_args* args, int type, char* longname, void* default_value, void* dst, char* hint);
static bool asked_for_help(int argc, char** argv);
static bool is_short_opt(char const* str);
static bool is_long_opt(char const* str);
static int match_short_opt(qc_args* args, int argn, char** argv, char** err);
static int match_long_opt(qc_args* args, int argn, char** argv, char** err);
static int parse_unsigned(char* str, size_t* dst);
static int parse_signed(char* str, ptrdiff_t* dst);
static int parse_double(char* str, double* dst);
static int parse_string(char* str, char** dst);

qc_args* qc_args_new() {
    qc_args* ret = emalloc(sizeof(qc_args));
    ret->flags = emalloc(sizeof(struct short_flag) * DEFAULT_ALLOC_SIZE);
    ret->flags_count = 0;
    ret->flags_capacity = DEFAULT_ALLOC_SIZE;
    ret->opts = emalloc(sizeof(struct long_opt) * DEFAULT_ALLOC_SIZE);
    ret->opts_count = 0;
    ret->opts_capacity = DEFAULT_ALLOC_SIZE;
    ret->positionals_index = 0;
    ret->positionals_count = 0;
    ret->extras_index = 0;
    ret->extras_count = 0;
    ret->help = NULL;
    ret->parsed = false;
    return ret;
}

void qc_args_free(qc_args* args) {
    assert(args != NULL);
    for (size_t i = 0; i < args->flags_count; ++i) {
        struct short_flag* flag = &args->flags[i];
        if (flag->hint != NULL) {
            free(flag->hint);
        }
    }
    for (size_t i = 0; i < args->opts_count; ++i) {
        struct long_opt* opt = &args->opts[i];
        free(opt->name);
        if (opt->hint != NULL) {
            free(opt->hint);
        }
        if (!opt->mandatory && opt->type == OPT_STRING) {
            free(opt->default_value.string_default);
        }
    }
    free(args->opts);
    free(args->flags);
    free(args);
}

void qc_args_set_help(qc_args* args, void (*help) (void*), void* help_data) {
    assert(args != NULL);
    args->help = help;
    args->help_data = help_data;
}

void qc_args_call_help(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("Fatal error: qc_args_call_help() should be called after qc_args_parse()");
    }
    call_help(args);
}

int qc_args_parse(qc_args* args, int argc, char** argv, char** err) {
    assert(args != NULL);
    if (args->parsed) {
        die("qc_args_parse() should be called only once on a single `args' handle");
    } else {
        args->parsed = true;
    }
    args->program_name = argv[0];
    if (asked_for_help(argc, argv)) {
        call_help(args);
    }
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            if (i < argc - 1) {
                args->extras_index = i + 1;
                args->extras_count = argc - i - 1;
            }
            break;
        }
        if (args->positionals_count == 0) {
            if (is_short_opt(argv[i])) {
                if (match_short_opt(args, i, argv, err) == -1) {
                    return -1;
                }
            } else if (is_long_opt(argv[i])) {
                if (match_long_opt(args, i, argv, err) == -1) {
                    return -1;
                }
            } else {
                args->positionals_index = i;
                args->positionals_count += 1;
            }
        } else {
            if (is_short_opt(argv[i]) || is_long_opt(argv[i])) {
                *err = sprintf_alloc(
                    "Unexpected opt \"%s\" after positional argument \"%s\"",
                    argv[i], argv[i - 1]);
                return -1;
            } else {
                args->positionals_count += 1;
            }
        }
    }
    for (size_t i = 0; i < args->opts_count; ++i) {
        struct long_opt* opt = &args->opts[i];
        if (opt->type == OPT_FLAG) {
            continue;
        } else if (!opt->mandatory) {
            if (!opt->provided) {
                switch (opt->type) {
                case OPT_UNSIGNED:
                    *opt->dst.unsigned_ptr = opt->default_value.unsigned_default;
                    break;
                case OPT_SIGNED:
                    *opt->dst.signed_ptr = opt->default_value.signed_default;
                    break;
                case OPT_DOUBLE:
                    *opt->dst.double_ptr = opt->default_value.double_default;
                    break;
                case OPT_STRING:
                    *opt->dst.string_ptr = emalloc(strlen(opt->default_value.string_default) + 1);
                    strcpy(*opt->dst.string_ptr, opt->default_value.string_default);
                    break;
                default: UNREACHABLE_CODE();
                }
            }
        } else {
            if (!opt->provided) {
                *err = sprintf_alloc("Argument --%s is required but not provided", opt->name);
                return -1;
            }
        }
    }
    return 0;
}

int qc_args_positionals_index(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_positionals_index() should only be called after qc_args_parse()");
    } else {
        return args->positionals_index;
    }
}

int qc_args_positionals_count(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_positionals_count() should only be called after qc_args_parse()");
    } else {
        return args->positionals_count;
    }
}

int qc_args_extras_index(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_extras_index() should only be called after qc_args_parse()");
    } else {
        return args->extras_index;
    }
}

int qc_args_extras_count(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_extras_count() should only be called after qc_args_parse()");
    } else {
        return args->extras_count;
    }
}

void qc_args_flag(qc_args* args, char shortname, char* longname, bool* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (shortname == 'h') {
        die("Flag -h is reserved for help");
    }
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    }
    array_push_back((void **) &args->flags, &args->flags_count, &args->flags_capacity, sizeof(struct short_flag));
    struct short_flag *flag = &args->flags[args->flags_count - 1];
    flag->name = shortname;
    if (hint != NULL) {
        flag->hint = emalloc(strlen(hint) + 1);
        strcpy(flag->hint, hint);
    } else {
        flag->hint = NULL;
    }
    flag->dst = dst;
    add_long_opt(args, OPT_FLAG, longname, NULL, dst, hint);
}

void qc_args_unsigned(qc_args* args, char* longname, size_t* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_UNSIGNED, longname, NULL, dst, hint);
    }
}

void qc_args_unsigned_default(qc_args* args, char* longname, size_t default_value, size_t* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_UNSIGNED, longname, &default_value, dst, hint);
    }
}

void qc_args_signed(qc_args* args, char* longname, ptrdiff_t* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_SIGNED, longname, NULL, dst, hint);
    }
}

void qc_args_signed_default(qc_args* args, char* longname, ptrdiff_t default_value, ptrdiff_t* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_SIGNED, longname, &default_value, dst, hint);
    }
}

void qc_args_double(qc_args* args, char* longname, double* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_DOUBLE, longname, NULL, dst, hint);
    }
}

void qc_args_double_default(qc_args* args, char* longname, double default_value, double* dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_DOUBLE, longname, &default_value, dst, hint);
    }
}

void qc_args_string(qc_args* args, char* longname, char** dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_STRING, longname, NULL, dst, hint);
    }
}

void qc_args_string_default(qc_args* args, char* longname, char* default_value, char** dst, char* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_STRING, longname, &default_value, dst, hint);
    }
}

__QC_NORETURN static void call_help(qc_args* args) {
    if (args->help != NULL) {
        args->help(args->help_data);
    } else {
        auto_help(args);
    }
    exit(EXIT_SUCCESS);
}

static void auto_help(qc_args* args) {
    fprintf(stderr, "Usage: %s [OPTIONS...]\n", args->program_name);

    fputs("\n Short flags:\n", stderr);
    for (size_t i = 0; i < args->flags_count; ++i) {
        struct short_flag* flag = &args->flags[i];
        if (flag->hint != NULL) {
            fprintf(stderr, "  -%c %s\n", flag->name, flag->hint);
        } else {
            fprintf(stderr, "  -%c\n", flag->name);
        }
    }

    fputs("\n Long options:\n", stderr);
    for (size_t i = 0; i < args->opts_count; ++i) {
        struct long_opt* opt = &args->opts[i];
        fprintf(stderr, "  --%s", opt->name);
        switch (opt->type) {
            case OPT_FLAG:
                break;
            case OPT_UNSIGNED:
                fputs("=UNSIGNED", stderr);
                break;
            case OPT_SIGNED:
                fputs("=SIGNED", stderr);
                break;
            case OPT_DOUBLE:
                fputs("=REAL", stderr);
                break;
            case OPT_STRING:
                fputs("=\"STRING\"", stderr);
                break;
            default: UNREACHABLE_CODE();
        }
        if (!opt->mandatory) {
            switch (opt->type) {
                case OPT_UNSIGNED:
                    fprintf(stderr, " ( default = %lu)", (unsigned long) opt->default_value.unsigned_default);
                    break;
                case OPT_SIGNED:
                    fprintf(stderr, " (default = %li)", (signed long) opt->default_value.signed_default);
                    break;
                case OPT_DOUBLE:
                    fprintf(stderr, " (default = %f)", opt->default_value.double_default);
                    break;
                case OPT_STRING:
                    fprintf(stderr, " (default = %s)", opt->default_value.string_default);
                    break;
                default: UNREACHABLE_CODE();
            }
        }
        if (opt->hint != NULL) {
            fprintf(stderr, " %s", opt->hint);
        }
        fputc('\n', stderr);
    }
}

static void array_push_back(void** array, size_t* count, size_t* capacity, size_t size) {
    *count += 1;
    if (*count == *capacity) {
        *capacity *= 2;
        *array = erealloc(*array, *capacity * size);
    }
}

static void add_long_opt(qc_args* args, int type, char* longname, void* default_value, void* dst, char* hint) {
    array_push_back((void**) &args->opts, &args->opts_count, &args->opts_capacity, sizeof(struct long_opt));
    struct long_opt* opt = &args->opts[args->opts_count - 1];
    opt->type = type;
    opt->name = emalloc(strlen(longname) + 1);
    strcpy(opt->name, longname);
    if (hint != NULL) {
        opt->hint = emalloc(strlen(hint) + 1);
        strcpy(opt->hint, hint);
    } else {
        opt->hint = NULL;
    }
    switch (type) {
        case OPT_FLAG:
            opt->dst.flag_ptr = dst;
            break;
        case OPT_UNSIGNED:
            opt->dst.unsigned_ptr = dst;
            break;
        case OPT_SIGNED:
            opt->dst.signed_ptr = dst;
            break;
        case OPT_DOUBLE:
            opt->dst.double_ptr = dst;
            break;
        case OPT_STRING:
            opt->dst.string_ptr = dst;
            break;
        default: UNREACHABLE_CODE();
    }
    if (default_value == NULL) {
        opt->mandatory = true;
        opt->provided = false;
    } else {
        opt->mandatory = false;
        opt->provided = false;
        switch (type) {
            case OPT_UNSIGNED:
                opt->default_value.unsigned_default = *((size_t*) default_value);
                break;
            case OPT_SIGNED:
                opt->default_value.signed_default = *((ptrdiff_t*) default_value);
                break;
            case OPT_DOUBLE:
                opt->default_value.double_default = *((double*) default_value);
                break;
            case OPT_STRING:
                opt->default_value.string_default = emalloc(strlen(*((char**) default_value)) + 1);
                strcpy(opt->default_value.string_default, *((char**) default_value));
                break;
            default: UNREACHABLE_CODE();
        }
    }
}

static bool asked_for_help(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            break;
        }
        if (is_long_opt(argv[i])) {
            if (strcmp(argv[i], "--help") == 0) {
                return true;
            }
        } else if (is_short_opt(argv[i])) {
            char* short_flags = &argv[i][1];
            for (size_t j = 0; j < strlen(short_flags); ++j) {
                if (short_flags[j] == 'h') {
                    return true;
                }
            }
        }
    }
    return false;
}

static bool is_short_opt(char const* str) {
    if (strlen(str) < 2) {
        return false;
    }
    return str[0] == '-' && str[1] != '-';
}

static bool is_long_opt(char const* str) {
    if (strlen(str) < 3) {
        return false;
    }
    return str[0] == '-' && str[1] == '-';
}

static int match_short_opt(qc_args* args, int argn, char** argv, char** err) {
    for (size_t to = strlen(argv[argn]), i = 1; i < to; ++i) {
        char c = argv[argn][i];
        if (c == 'h') {
            continue;
        }
        bool found = false;
        for (size_t j= 0; j < args->flags_count; ++j) {
            if (args->flags[j].name == c) {
                *args->flags[j].dst = true;
                found = true;
                break;
            }
        }
        if (!found) {
            *err = sprintf_alloc("Unknown flag: \"%c\"", argv[argn][i]);
            return -1;
        }
    }
    return 0;
}

static int match_long_opt(qc_args* args, int argn, char** argv, char** err) {
    for (size_t i = 0; i < args->opts_count; ++i) {
        if (strncmp(&argv[argn][2], args->opts[i].name, strlen(args->opts[i].name)) == 0) {
            args->opts[i].provided = true;
            switch (args->opts[i].type) {
                case OPT_FLAG:
                    *args->opts[i].dst.flag_ptr = true;
                    return 0;
                case OPT_UNSIGNED:
                    if (parse_unsigned(argv[argn], args->opts[i].dst.unsigned_ptr) == -1) {
                        *err = sprintf_alloc("Could not parse \"%s\" as unsigned integer", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_SIGNED:
                    if (parse_signed(argv[argn], args->opts[i].dst.signed_ptr) == -1) {
                        *err = sprintf_alloc("Could not parse \"%s\" as signed integer", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_DOUBLE:
                    if (parse_double(argv[argn], args->opts[i].dst.double_ptr) == -1) {
                        *err = sprintf_alloc("Could not parse \"%s\" as floating point value", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_STRING:
                    if (parse_string(argv[argn], args->opts[i].dst.string_ptr) == -1) {
                        *err = sprintf_alloc("Could not parse string from \"%s\"", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                default: UNREACHABLE_CODE();
            }
        }
    }
    *err = sprintf_alloc("Unknown argument: \"%s\"", argv[argn]);
    return -1;
}

static int parse_unsigned(char* str, size_t* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    if (val[0] == '-') {
        // strtoull does not provide any means
        // of differentiating between signed and unsigned input...
        return -1;
    }
    char* endptr;
    errno = 0;
    unsigned long long u = strtoull(val, &endptr, 0);
    if (errno != 0 || *endptr != '\0') {
        return -1;
    } else {
        *dst = u % SIZE_MAX;
        return 0;
    }
}

static int parse_signed(char* str, ptrdiff_t* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    char* endptr;
    errno = 0;
    signed long long s = strtoll(val, &endptr, 0);
    if (errno != 0 || *endptr != '\0') {
        return -1;
    } else {
        *dst = s % PTRDIFF_MAX;
        return 0;
    }
}

static int parse_double(char* str, double* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    char* endptr;
    errno = 0;
    double d = strtod(val, &endptr);
    if (errno != 0 || *endptr != '\0') {
        return -1;
    } else {
        *dst = d;
        return 0;
    }
}

static int parse_string(char* str, char** dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        return -1;
    } else {
        ++val;
    }
    if (val[0] == '"' && val[strlen(val) - 1] == '"') {
        ++val;
        *dst = emalloc(strlen(val) + 1);
        strcpy(*dst, val);
        (*dst)[strlen(*dst) - 1] = '\0';
    } else {
        *dst = emalloc(strlen(val) + 1);
        strcpy(*dst, val);
    }
    return 0;
}
