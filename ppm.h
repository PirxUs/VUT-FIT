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

/** 
 * @defgroup PPM PPM
 */

/**
 * @struct ppm
 * @brief Struktura pro ulozeni dat obrazku formatu ppm.
 *
 * @var ppm::xsize
 * Pocet pixelu v horizontalni rovine.
 * @var ppm::ysize
 * Pocet pixelu ve vertikalni rovine.
 * @var ppm::data
 * Pole pro ulozeni binarnich dat obrazku.
 */
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

/**
 * @brief Nacte binarni data obrazku ze souboru do struktury ppm. 
 *
 * @param filename Jmeno souboru, ktery chceme nacist.
 *
 * @return Vraci pointer na strukturu ppm s nactenymi daty obrazku.
 * V pripade neuspechu vraci NULL.
 *
 * @ingroup PPM
 */
struct ppm *ppm_read(const char *filename);

/**
 * @brief Uvolni pamet dynamicky alokovanou pro strukturu ppm.
 *
 * @param p Pointer na struktru ppm, jehoz pamet chceme uvolnit.
 *
 * @return void
 *
 * @ingroup PPM
 */
void ppm_free(struct ppm *p);

#endif
