/**
 *	@file	error.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Modul implementujici funkce pro pripad vyskytu chybovych stavu.
 *	@note	Reseni: IJC-DU1, priklad b)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

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
