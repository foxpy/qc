#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "qc/args.h"
#include "qc/string.h"
#include "qc/utils.h"
#include "qc/error.h"
#include "args_impl.h"

void auto_help(qc_args* args) {
    if (args->brief != NULL) {
        fprintf(stderr, "%s\n", args->brief);
    }
    fprintf(stderr, "Usage: %s [OPTIONS...]\n", args->program_name);

    if (args->flags_count != 0) {
        fputs("\n Short flags:\n", stderr);
        for (size_t i = 0; i < args->flags_count; ++i) {
            struct short_flag *flag = &args->flags[i];
            if (flag->hint != NULL) {
                fprintf(stderr, "  -%c %s\n", flag->name, flag->hint);
            } else {
                fprintf(stderr, "  -%c\n", flag->name);
            }
        }
    }

    if (args->opts_count != 0) {
        fputs("\n Long options:\n", stderr);
        for (size_t i = 0; i < args->opts_count; ++i) {
            struct long_opt *opt = &args->opts[i];
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
                default:
                    QC_UNREACHABLE_CODE();
            }
            if (!opt->mandatory) {
                switch (opt->type) {
                    case OPT_UNSIGNED:
                        fprintf(stderr, " ( default = %zu)", opt->default_value.unsigned_default);
                        break;
                    case OPT_SIGNED:
                        fprintf(stderr, " (default = %ti)", opt->default_value.signed_default);
                        break;
                    case OPT_DOUBLE:
                        fprintf(stderr, " (default = %f)", opt->default_value.double_default);
                        break;
                    case OPT_STRING:
                        fprintf(stderr, " (default = %s)", opt->default_value.string_default);
                        break;
                    default:
                        QC_UNREACHABLE_CODE();
                }
            }
            if (opt->hint != NULL) {
                fprintf(stderr, " %s", opt->hint);
            }
            fputc('\n', stderr);
        }
    }
}

void add_long_opt(qc_args* args, int type, char const* longname, void* default_value, void* dst, char const* hint) {
    array_push_back((void**) &args->opts, &args->opts_count, &args->opts_capacity, sizeof(struct long_opt));
    struct long_opt* opt = &args->opts[args->opts_count - 1];
    opt->type = type;
    opt->provided = false;
    opt->name = qc_malloc(strlen(longname) + 1);
    strcpy(opt->name, longname);
    if (hint != NULL) {
        opt->hint = qc_malloc(strlen(hint) + 1);
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
        default: QC_UNREACHABLE_CODE();
    }
    if (default_value == NULL) {
        opt->mandatory = true;
    } else {
        opt->mandatory = false;
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
                opt->default_value.string_default = qc_malloc(strlen(*((char **) default_value)) + 1);
                strcpy(opt->default_value.string_default, *((char**) default_value));
                break;
            default: QC_UNREACHABLE_CODE();
        }
    }
}

bool asked_for_help(int argc, char* const* argv) {
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

bool is_short_opt(char const* str) {
    if (strlen(str) < 2) {
        return false;
    }
    return str[0] == '-' && str[1] != '-';
}

bool is_long_opt(char const* str) {
    if (strlen(str) < 3) {
        return false;
    }
    return str[0] == '-' && str[1] == '-';
}

int match_short_opt(qc_args* args, int argn, char* const* argv, qc_err* err) {
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
            qc_err_set(err, "Unknown flag: \"%c\"", argv[argn][i]);
            return -1;
        }
    }
    return 0;
}

int match_long_opt(qc_args* args, int argn, char* const* argv, qc_err* err) {
    for (size_t i = 0; i < args->opts_count; ++i) {
        size_t argname_length = strlen(args->opts[i].name);
        if (strncmp(&argv[argn][2], args->opts[i].name, argname_length) == 0 &&
            (argv[argn][2 + argname_length] == '\0' || argv[argn][2 + argname_length] == '=')) {
            args->opts[i].provided = true;
            switch (args->opts[i].type) {
                case OPT_FLAG:
                    *args->opts[i].dst.flag_ptr = true;
                    return 0;
                case OPT_UNSIGNED:
                    if (parse_unsigned(argv[argn], args->opts[i].dst.unsigned_ptr) == -1) {
                        qc_err_set(err, "Could not parse \"%s\" as unsigned integer", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_SIGNED:
                    if (parse_signed(argv[argn], args->opts[i].dst.signed_ptr) == -1) {
                        qc_err_set(err, "Could not parse \"%s\" as signed integer", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_DOUBLE:
                    if (parse_double(argv[argn], args->opts[i].dst.double_ptr) == -1) {
                        qc_err_set(err, "Could not parse \"%s\" as floating point value", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                case OPT_STRING:
                    if (parse_string(argv[argn], args->opts[i].dst.string_ptr) == -1) {
                        qc_err_set(err, "Could not parse string from \"%s\"", argv[argn]);
                        return -1;
                    } else {
                        return 0;
                    }
                default: QC_UNREACHABLE_CODE();
            }
        }
    }
    qc_err_set(err, "Unknown argument: \"%s\"", argv[argn]);
    return -1;
}

int parse_unsigned(char* str, size_t* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    if (qc_str_to_unsigned(val, dst, NULL) == QC_SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}

int parse_signed(char* str, ptrdiff_t* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    if (qc_str_to_signed(val, dst, NULL) == QC_SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}

int parse_double(char* str, double* dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        val = str;
    } else {
        ++val;
    }
    if (qc_str_to_double(val, dst, NULL) == QC_SUCCESS) {
        return 0;
    } else {
        return -1;
    }
}

int parse_string(char* str, char** dst) {
    char* val;
    if ((val = strchr(str, '=')) == NULL) {
        return -1;
    } else {
        ++val;
    }
    if (val[0] == '"' && val[strlen(val) - 1] == '"') {
        ++val;
        *dst = qc_malloc(strlen(val) + 1);
        strcpy(*dst, val);
        (*dst)[strlen(*dst) - 1] = '\0';
    } else {
        *dst = qc_malloc(strlen(val) + 1);
        strcpy(*dst, val);
    }
    return 0;
}

void array_push_back(void** array, size_t* count, size_t* capacity, size_t size) {
    *count += 1;
    if (*count == *capacity) {
        *capacity *= 2;
        *array = qc_realloc(*array, *capacity * size);
    }
}
