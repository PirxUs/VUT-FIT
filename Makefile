CFLAGS= -std=c11 -O2 -Wall -Wextra -pedantic -g -lm
primes: primes.c bit_array.h error.h error.c eratosthenes.c ppm.h ppm.c

inline: primes.c bit_array.h error.h error.c eratosthenes.c ppm.h ppm.c
	gcc $(CFLAGS) -DUSE_INLINE primes.c error.c eratosthenes.c ppm.c -o primes-i

decode: steg-decode.c bit_array.h error.h error.c eratosthenes.c ppm.h ppm.c
	gcc $(CFLAGS) -DUSE_INLINE steg-decode.c error.c eratosthenes.c ppm.c -o steg-decode
clean:
	-rm -f primes primes.o primes-i steg-decode
