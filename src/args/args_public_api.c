#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "qc/args.h"
#include "qc/utils.h"
#include "args_impl.h"

qc_args* qc_args_new(void) {
    qc_args* ret = qc_malloc(sizeof(qc_args));
    ret->flags = qc_malloc(sizeof(struct short_flag) * DEFAULT_ALLOC_SIZE);
    ret->flags_count = 0;
    ret->flags_capacity = DEFAULT_ALLOC_SIZE;
    ret->opts = qc_malloc(sizeof(struct long_opt) * DEFAULT_ALLOC_SIZE);
    ret->opts_count = 0;
    ret->opts_capacity = DEFAULT_ALLOC_SIZE;
    ret->positionals_index = 0;
    ret->positionals_count = 0;
    ret->extras_index = 0;
    ret->extras_count = 0;
    ret->help_cb = NULL;
    ret->help_data = NULL;
    ret->program_name = NULL;
    ret->brief = NULL;
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
        if (opt->type == OPT_STRING) {
            if (!opt->mandatory || opt->provided) {
                free(*opt->dst.string_ptr);
            }
            if (!opt->mandatory) {
                free(opt->default_value.string_default);
            }
        }
    }
    if (args->program_name != NULL) {
        free(args->program_name);
    }
    if (args->brief != NULL) {
        free(args->brief);
    }
    free(args->opts);
    free(args->flags);
    free(args);
}

void qc_args_set_help(qc_args* args, help_function help_cb, void* help_data) {
    assert(args != NULL);
    assert(help_cb != NULL);
    args->help_cb = help_cb;
    args->help_data = help_data;
}

void qc_args_set_brief(qc_args* args, char const* brief) {
    assert(args != NULL);
    assert(brief != NULL);
    args->brief = qc_malloc(strlen(brief) + 1);
    strcpy(args->brief, brief);
}

void qc_args_call_help(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        qc_die("Fatal error: qc_args_call_help() should be called after qc_args_parse()");
    } else if (args->help_cb != NULL) {
        args->help_cb(args->help_data);
    } else {
        auto_help(args);
    }
}

qc_result qc_args_parse(qc_args* args, int argc, char** argv, qc_err* err) {
    assert(args != NULL);
    assert(argc != 0);
    assert(argv != NULL);
    if (args->parsed) {
        qc_die("qc_args_parse() should be called only once on a single `args' handle");
    } else {
        args->parsed = true;
    }
    args->program_name = qc_malloc(strlen(argv[0]) + 1);
    strcpy(args->program_name, argv[0]);
    if (asked_for_help(argc, argv)) {
        qc_args_call_help(args);
        exit(EXIT_SUCCESS);
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
                if (match_short_opt(args, i, argv, err) == QC_FAILURE) {
                    return QC_FAILURE;
                }
            } else if (is_long_opt(argv[i])) {
                if (match_long_opt(args, i, argv, err) == QC_FAILURE) {
                    return QC_FAILURE;
                }
            } else {
                args->positionals_index = i;
                args->positionals_count += 1;
            }
        } else {
            if (is_short_opt(argv[i]) || is_long_opt(argv[i])) {
                qc_err_set(err, "Unexpected opt \"%s\" after positional argument \"%s\"", argv[i], argv[i - 1]);
                return QC_FAILURE;
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
                    case OPT_UNSIGNED: *opt->dst.unsigned_ptr = opt->default_value.unsigned_default; break;
                    case OPT_SIGNED: *opt->dst.signed_ptr = opt->default_value.signed_default; break;
                    case OPT_DOUBLE: *opt->dst.double_ptr = opt->default_value.double_default; break;
                    case OPT_STRING:
                        *opt->dst.string_ptr = qc_malloc(strlen(opt->default_value.string_default) + 1);
                        strcpy(*opt->dst.string_ptr, opt->default_value.string_default);
                        break;
                    default: QC_UNREACHABLE_CODE();
                }
            }
        } else {
            if (!opt->provided) {
                qc_err_set(err, "Argument --%s is required but not provided", opt->name);
                return QC_FAILURE;
            }
        }
    }
    return QC_SUCCESS;
}

int qc_args_positionals_index(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        qc_die("qc_args_positionals_index() should only be called after qc_args_parse()");
    } else {
        return args->positionals_index;
    }
}

int qc_args_positionals_count(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        qc_die("qc_args_positionals_count() should only be called after qc_args_parse()");
    } else {
        return args->positionals_count;
    }
}

int qc_args_extras_index(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        qc_die("qc_args_extras_index() should only be called after qc_args_parse()");
    } else {
        return args->extras_index;
    }
}

int qc_args_extras_count(qc_args* args) {
    assert(args != NULL);
    if (!args->parsed) {
        qc_die("qc_args_extras_count() should only be called after qc_args_parse()");
    } else {
        return args->extras_count;
    }
}

void qc_args_flag(qc_args* args, char shortname, char const* longname, bool* dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (shortname == 'h') {
        qc_die("Flag -h is reserved for help");
    }
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    }
    array_push_back((void**) &args->flags, &args->flags_count, &args->flags_capacity, sizeof(struct short_flag));
    struct short_flag* flag = &args->flags[args->flags_count - 1];
    flag->name = shortname;
    if (hint != NULL) {
        flag->hint = qc_malloc(strlen(hint) + 1);
        strcpy(flag->hint, hint);
    } else {
        flag->hint = NULL;
    }
    flag->dst = dst;
    *dst = false;
    add_long_opt(args, OPT_FLAG, longname, NULL, dst, hint);
}

void qc_args_unsigned(qc_args* args, char const* longname, size_t* dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_UNSIGNED, longname, NULL, dst, hint);
    }
}

void qc_args_unsigned_default(qc_args* args, char const* longname, size_t default_value, size_t* dst,
                              char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_UNSIGNED, longname, &default_value, dst, hint);
    }
}

void qc_args_signed(qc_args* args, char const* longname, ptrdiff_t* dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_SIGNED, longname, NULL, dst, hint);
    }
}

void qc_args_signed_default(qc_args* args, char const* longname, ptrdiff_t default_value, ptrdiff_t* dst,
                            char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_SIGNED, longname, &default_value, dst, hint);
    }
}

void qc_args_double(qc_args* args, char const* longname, double* dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_DOUBLE, longname, NULL, dst, hint);
    }
}

void qc_args_double_default(qc_args* args, char const* longname, double default_value, double* dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_DOUBLE, longname, &default_value, dst, hint);
    }
}

void qc_args_string(qc_args* args, char const* longname, char const** dst, char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_STRING, longname, NULL, dst, hint);
    }
}

void qc_args_string_default(qc_args* args, char const* longname, char* default_value, char const** dst,
                            char const* hint) {
    assert(args != NULL);
    assert(longname != NULL);
    assert(dst != NULL);
    if (strcmp(longname, "help") == 0) {
        qc_die("Flag --help is reserved for help");
    } else {
        add_long_opt(args, OPT_STRING, longname, &default_value, dst, hint);
    }
}
