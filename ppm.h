#ifndef PPM_HEADER
#define PPM_HEADER

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[]; //RBG, 3*xsize*ysize
};

struct ppm *ppm_read(const char *filename);

void ppm_free(struct ppm *p);

#endif
