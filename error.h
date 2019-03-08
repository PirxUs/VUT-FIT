/**
 *	@file	error.h
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Rozhrani k modulu error.c.
 *	@note	Reseni: IJC-DU1, priklad a)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef ERROR_HEADER
#define ERROR_HEADER

void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
