#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"

void warning_msg(const char *fmt, ...) {
    va_list list;

    va_start(list, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, list);
    fprintf(stderr, "\n");
    va_end(list);
}

void error_exit(const char *fmt, ...) {
    va_list list;

    va_start(list, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, list);
    fprintf(stderr, "\n");
    va_end(list);

    exit(1);
}
