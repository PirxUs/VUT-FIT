CFLAGS= -std=c11 -O2 -Wall -Wextra -pedantic -g -lm
INLINE= -DUSE_INLINE

all: primes inline decode

inline: primes-i

decode: steg-decode

run: primes primes-i
	time ./primes
	time ./primes-i

#basic target builds
primes: primes.o error.o eratosthenes.o bit_array.o
	gcc $(CFLAGS) primes.o bit_array.o error.o eratosthenes.o -o primes

primes-i: primes-i.o error.o eratosthenes-i.o bit_array-i.o
	gcc $(CFLAGS) primes-i.o bit_array-i.o error.o eratosthenes-i.o -o primes-i

steg-decode: steg-decode-i.o error.o eratosthenes-i.o ppm.o bit_array-i.o
	gcc $(CFLAGS) steg-decode-i.o bit_array-i.o error.o eratosthenes-i.o ppm.o -o steg-decode

#object files
primes.o: primes.c
	gcc $(CFLAGS) -c -o primes.o primes.c

bit_array.o: bit_array.c bit_array.h
	gcc $(CFLAGS) -c -o bit_array.o bit_array.c

error.o: error.c error.h
	gcc $(CFLAGS) -c -o error.o error.c 

eratosthenes.o: eratosthenes.c eratosthenes.h
	gcc $(CFLAGS) -c -o eratosthenes.o eratosthenes.c

ppm.o: ppm.c ppm.h
	gcc $(CFLAGS) -c -o ppm.o ppm.c

#inline object files
primes-i.o: primes.c
	gcc $(CFLAGS) $(INLINE) -c -o primes-i.o primes.c

eratosthenes-i.o: eratosthenes.c eratosthenes.h
	gcc $(CFLAGS) $(INLINE) -c -o eratosthenes-i.o eratosthenes.c

steg-decode-i.o: steg-decode.c
	gcc $(CFLAGS) $(INLINE) -c -o steg-decode-i.o steg-decode.c

bit_array-i.o: bit_array.c bit_array.h
	gcc $(CFLAGS) $(INLINE) -c -o bit_array-i.o bit_array.c


#other targets
clean:
	rm -f primes primes-i steg-decode *.o
