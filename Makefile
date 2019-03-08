#-------------------------------------------------
#  FILE:   Makefile
#  AUTHOR: Simon Sedlacek, FIT
#  EMAIL:  xsedla1h@stud.fit.vutbr.cz
#  DATE:   10.3.2019
#  BRIEF:  Makefile pro preklad prvniho domaciho ukolu z predmetu IJC.
#  NOTE: Reseni: IJC-DU1
#-------------------------------------------------

CFLAGS= -std=c11 -O2 -Wall -Wextra -pedantic -g -lm
INLINE= -DUSE_INLINE

# hlavni cile pro preklad a spusteni
all: primes inline decode

run: primes primes-i
	time ./primes
	time ./primes-i

#
# vedlejsi redundantni cile pro vetsi prehlednost
inline: primes-i

decode: steg-decode

# zakladni cile prekladu
primes: primes.o error.o eratosthenes.o bit_array.o
	gcc $(CFLAGS) primes.o error.o eratosthenes.o bit_array.o -o primes

primes-i: primes-i.o error.o eratosthenes-i.o bit_array-i.o
	gcc $(CFLAGS) primes-i.o error.o eratosthenes-i.o bit_array-i.o -o primes-i

steg-decode: steg-decode-i.o error.o eratosthenes-i.o ppm.o bit_array-i.o
	gcc $(CFLAGS) steg-decode-i.o bit_array-i.o error.o eratosthenes-i.o ppm.o -o steg-decode

# objektove soubory
primes.o: primes.c
	gcc $(CFLAGS) -c -o primes.o primes.c

bit_array.o: bit_array.c bit_array.h
	gcc $(CFLAGS) -c -o bit_array.o bit_array.c

eratosthenes.o: eratosthenes.c eratosthenes.h
	gcc $(CFLAGS) -c -o eratosthenes.o eratosthenes.c

error.o: error.c error.h
	gcc $(CFLAGS) -c -o error.o error.c 

ppm.o: ppm.c ppm.h
	gcc $(CFLAGS) -c -o ppm.o ppm.c

# objektove soubory s inline funkcemi
primes-i.o: primes.c
	gcc $(CFLAGS) $(INLINE) -c -o primes-i.o primes.c

bit_array-i.o: bit_array.c bit_array.h
	gcc $(CFLAGS) $(INLINE) -c -o bit_array-i.o bit_array.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h
	gcc $(CFLAGS) $(INLINE) -c -o eratosthenes-i.o eratosthenes.c

steg-decode-i.o: steg-decode.c
	gcc $(CFLAGS) $(INLINE) -c -o steg-decode-i.o steg-decode.c

# dalsi cile
clean:
	rm -f primes primes-i steg-decode *.o
