#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ppm.h"
#include "error.h"

struct ppm *ppm_read(const char *filename) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        warning_msg("Nepodarilo se otevrit obrazek '%s'", filename);
        return NULL;
    }
    
    unsigned xsize, ysize, colorValue;
    char fileID[10] = {0};

    fscanf(file, "%s %u %u %u", fileID, &xsize, &ysize, &colorValue);

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

    //posun v bufferu na zacatek dalsiho radku
    fgets(p->data, 10, file);

    fread(p->data, 1, bufferLength, file);

    fclose(file);
    return p;
}

void ppm_free(struct ppm *p) {
    free(p);
}
