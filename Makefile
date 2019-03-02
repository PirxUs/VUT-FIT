CFLAGS= -std=c11 -O0 -Wall -Wextra -pedantic -g
primes: primes.c bit_array.h error.h error.c

inline: primes.c bit_array.h error.h error.c
	gcc $(CFLAGS) -DUSE_INLINE primes.c error.c -o primes

clean:
	-rm -f primes primes.o error.o
