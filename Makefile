CFLAGS= -std=c11 -O2 -Wall -Wextra -pedantic -g -lm
INLINE= -DUSE_INLINE

all: primes primes-i steg-decode

run: primes primes-i
	time ./primes
	time ./primes-i

primes: primes.o error.o eratosthenes.o bit_array.h
	gcc $(CFLAGS) primes.o error.o eratosthenes.o -o primes

primes-i: primes-i.o error.o eratosthenes-i.o bit_array.h
	gcc $(CFLAGS) primes-i.o error.o eratosthenes-i.o -o primes-i

steg-decode: steg-decode-i.o error.o eratosthenes-i.o ppm.o bit_array.h
	gcc $(CFLAGS) steg-decode-i.o error.o eratosthenes-i.o ppm.o -o steg-decode

#object files

primes.o:
	gcc $(CFLAGS) -c -o primes.o primes.c

error.o:
	gcc $(CFLAGS) -c -o error.o error.c 

eratosthenes.o:
	gcc $(CFLAGS) -c -o eratosthenes.o eratosthenes.c

ppm.o:
	gcc $(CFLAGS) -c -o ppm.o ppm.c

#inline object files
primes-i.o:
	gcc $(CFLAGS) $(INLINE) -c -o primes-i.o primes.c

eratosthenes-i.o:
	gcc $(CFLAGS) $(INLINE) -c -o eratosthenes-i.o eratosthenes.c

steg-decode-i.o:
	gcc $(CFLAGS) $(INLINE) -c -o steg-decode-i.o steg-decode.c

clean:
	rm -f primes primes-i steg-decode *.o
