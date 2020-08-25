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
    bool* dst;
};

struct long_opt {
    char* name;
    int type;
    union {
        bool* flag_ptr;
        size_t* unsigned_ptr;
        ptrdiff_t* signed_ptr;
        double* double_ptr;
        char** string_ptr;
    } dst;
};

struct positional {
    char** dst;
};

struct qc_args {
    struct short_flag* flags;
    size_t flags_count;
    size_t flags_capacity;
    struct long_opt* opts;
    size_t opts_count;
    size_t opts_capacity;
    struct positional* positionals;
    size_t positionals_count;
    size_t positionals_capacity;
    void (*help) (void*);
    void* help_data;
    size_t positionals_found;
    int extra_index;
    bool parsed;
};

__QC_NORETURN static void call_help(qc_args* args);
static void array_push_back(void** array, size_t* count, size_t* capacity, size_t size);
static void add_long_opt(qc_args* args, int type, char* longname, void* dst);
static bool asked_for_help(int argc, char** argv);
static bool is_short_opt(char const* str);
static bool is_long_opt(char const* str);
static int match_short_opt(qc_args* args, int argn, char** argv, char** err);
static int match_long_opt(qc_args* args, int argn, char** argv, char** err);
static int match_pos_opt(qc_args* args, size_t num, char* str, char** err);
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
    ret->positionals = emalloc(sizeof(struct positional) * DEFAULT_ALLOC_SIZE);
    ret->positionals_count = 0;
    ret->positionals_capacity = DEFAULT_ALLOC_SIZE;
    ret->help = NULL;
    ret->parsed = false;
    return ret;
}

void qc_args_free(qc_args* args) {
    assert(args != NULL);
    for (size_t i = 0; i < args->opts_count; ++i) {
        free(args->opts[i].name);
    }
    free(args->opts);
    free(args->flags);
    free(args->positionals);
    free(args);
}

void qc_args_set_help(qc_args* args, void (*help) (void*), void* help_data) {
    assert(args != NULL);
    args->help = help;
    args->help_data = help_data;
}

int qc_args_parse(qc_args* args, int argc, char** argv, char** err) {
    assert(args != NULL);
    if (args->parsed) {
        die("qc_args_parse() should be called only once on a single `struct args'");
    } else {
        args->parsed = true;
    }
    if (asked_for_help(argc, argv)) {
        call_help(args);
    }
    size_t pos_arg_num  = 0;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            args->extra_index = i;
            return 0;
        }
        if (pos_arg_num == 0) {
            if (is_short_opt(argv[i])) {
                if (match_short_opt(args, i, argv, err) == -1) {
                    return -1;
                }
            } else if (is_long_opt(argv[i])) {
                if (match_long_opt(args, i, argv, err) == -1) {
                    return -1;
                }
            } else {
                ++pos_arg_num;
                if (match_pos_opt(args, pos_arg_num - 1, argv[i], err) == -1) {
                    return -1;
                }
            }
        } else {
            if (is_short_opt(argv[i]) || is_long_opt(argv[i])) {
                *err = sprintf_alloc(
                    "Unexpected opt \"%s\" after positional argument \"%s\"",
                    argv[i], argv[i - 1]);
                return -1;
            } else {
                ++pos_arg_num;
                if (match_pos_opt(args, pos_arg_num - 1, argv[i], err) == -1) {
                    return -1;
                }
            }
        }
    }
    args->positionals_found = pos_arg_num;
    return 0;
}

size_t qc_args_num_positionals(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_num_positionals() should only be called after qc_args_parse()");
    } else {
        return args->positionals_found;
    }
}

int qc_args_extra_index(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        die("qc_args_extra_index() should only be called after qc_args_parse()");
    } else {
        return args->extra_index;
    }
}

void qc_args_flag(qc_args* args, char shortname, char* longname, bool* dst) {
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
    flag->dst = dst;
    add_long_opt(args, OPT_FLAG, longname, dst);
}

void qc_args_unsigned(qc_args* args, char* longname, size_t* dst) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_UNSIGNED, longname, dst);
    }
}

void qc_args_signed(qc_args* args, char* longname, ptrdiff_t* dst) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_SIGNED, longname, dst);
    }
}

void qc_args_double(qc_args* args, char* longname, double* dst) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_DOUBLE, longname, dst);
    }
}

void qc_args_string(qc_args* args, char* longname, char** dst) {
    assert(args != NULL);
    assert(longname != NULL);
    if (strcmp(longname, "help") == 0) {
        die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_STRING, longname, dst);
    }
}

void qc_args_positional(qc_args* args, char** dst) {
    assert(args != NULL);
    array_push_back((void**) &args->positionals, &args->positionals_count,
                    &args->positionals_capacity, sizeof(struct positional));
    struct positional* pos = &args->positionals[args->positionals_count - 1];
    pos->dst = dst;
}


__QC_NORETURN static void call_help(qc_args* args) {
    if (args->help != NULL) {
        args->help(args->help_data);
        exit(EXIT_SUCCESS);
    } else {
        fputs("Error: no help is available\n", stderr);
        exit(EXIT_FAILURE);
    }
}

static void array_push_back(void** array, size_t* count, size_t* capacity, size_t size) {
    *count += 1;
    if (*count == *capacity) {
        *capacity *= 2;
        *array = erealloc(*array, *capacity * size);
    }
}

static void add_long_opt(qc_args* args, int type, char* longname, void* dst) {
    array_push_back((void**) &args->opts, &args->opts_count, &args->opts_capacity, sizeof(struct long_opt));
    struct long_opt* opt = &args->opts[args->opts_count - 1];
    opt->type = type;
    opt->name = emalloc(strlen(longname) + 1);
    strcpy(opt->name, longname);
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
}

static bool asked_for_help(int argc, char** argv) {
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--") == 0) {
            break;
        }
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            return true;
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

static int match_pos_opt(qc_args* args, size_t num, char* str, char** err) {
    if (num >= args->positionals_count) {
        *err = sprintf_alloc("Unexpected positional argument \"%s\": too much positional arguments", str);
        return -1;
    } else {
        *args->positionals[num].dst = emalloc(strlen(str) + 1);
        strcpy(*args->positionals[num].dst, str);
        return 0;
    }
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
