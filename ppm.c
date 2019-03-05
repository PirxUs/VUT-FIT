#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "error.h"

#define SIZE_LIMIT 3*8000*8000

struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        warning_msg("Nepodarilo se otevrit obrazek '%s'", filename);
        return NULL;
    }
    
    unsigned xsize, ysize, colorValue;
    char fileID[10] = {0};

    /* tento formatovaci retezec je navrzen tak, aby presne odpovidal
     * specifikaci hlavicky obrazku ve formatu ppm. Pokud budeme v obrazku
     * cist dale, zaciname cist binarni data */
    fscanf(file, "%s %u %u %u ", fileID, &xsize, &ysize, &colorValue);

    if (strcmp(fileID, "P6")) {
        warning_msg("Nepodporovany format obrazku: %s", fileID);
        fclose(file);
        return NULL;
    }

    if (colorValue != 255) {
        warning_msg("Nepodporovany format barev obrazku");
        fclose(file);
        return NULL;
    }

    struct ppm *p;
    unsigned long bufferLength = 3 * xsize * ysize;

    if (bufferLength > SIZE_LIMIT) {
        warning_msg("Obrazek je prilis velky");
        fclose(file);
        return NULL;
    }

    p = malloc(sizeof(struct ppm) + bufferLength);
    
    if (p == NULL) {
        warning_msg("Nepodarilo se alokovat pamet pro ppm strukturu");
        fclose(file);
        return NULL;
    }

    p->xsize = xsize;
    p->ysize = ysize;

    if (p->data == NULL) {
        warning_msg("Nepodarilo se alokovat pamet pro RGB buffer obrazku");
        fclose(file);
        free(p);
        return NULL;
    }

    fread(p->data, 1, bufferLength, file);

    fclose(file);
    return p;
}

void ppm_free(struct ppm *p) {
    free(p);
}
