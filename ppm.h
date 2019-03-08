/**
 *	@file	ppm.h
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Rozhrani modulu ppm.c.
 *	@note	Reseni: IJC-DU1, priklad b)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#ifndef PPM_HEADER
#define PPM_HEADER

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif
