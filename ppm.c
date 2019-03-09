/**
 *	@file	ppm.c
 *	@author	Simon Sedlacek, FIT
 *	@date	10.3.2019
 *	@brief  Modul implementujici funkce pro nacitani binarnich dat z obrazku formatu ppm.
 *	@note	Reseni: IJC-DU1, priklad b)
 *	Prelozeno: gcc 8.3.1 - Fedora release 29 (Twenty Nine) x86_64 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "error.h"

/* Implementacni limit velikosti dat nacitaneho obrazku. */
#define SIZE_LIMIT (3*8000*8000)

struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "rb");
    struct ppm *image;

    if (file == NULL) {
        warning_msg("Nepodarilo se otevrit obrazek '%s'", filename);
        return NULL;
    }
    
    unsigned xsize, ysize, colorValue;
    char fileID[10] = {0};

    /* Tento formatovaci retezec je navrzen tak, aby presne odpovidal
     * specifikaci hlavicky obrazku ve formatu ppm. Pokud budeme v obrazku
     * cist dale, zaciname cist binarni data */
    fscanf(file, "%9s %u %u %u ", fileID, &xsize, &ysize, &colorValue);
    unsigned long bufferLength = 3 * xsize * ysize;

    /* Ruzne chybove stavy...  */
    if (strcmp(fileID, "P6")) {
        warning_msg("Nepodporovany format obrazku: %s", fileID);
        goto error;
    }

    if (bufferLength > SIZE_LIMIT) {
        warning_msg("Obrazek je prilis velky");
        goto error;
    }

    if (colorValue != 255) {
        warning_msg("Nepodporovany format barev obrazku");
        goto error;
    }

    /* Alokace pameti pro nacteni dat obrazku */
    image = malloc(sizeof(struct ppm) + bufferLength);
    
    if (image == NULL) {
        warning_msg("Nepodarilo se alokovat pamet pro ppm strukturu");
        goto error;
    }

    image->xsize = xsize;
    image->ysize = ysize;

    fread(image->data, 1, bufferLength, file);

    if (ferror(file)) {
        warning_msg("Chyba pri nacitani dat obrazku");
        goto error_free;
    }

    fclose(file);
    return image;

    /* Navesti pro osetreni chybovych stavu */
error_free:
    ppm_free(image);
error:
    fclose(file);
    return NULL;
}

void ppm_free(struct ppm *p) {
    free(p);
}
