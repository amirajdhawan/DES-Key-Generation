mainDes: mainDes.o BitOperations.o keyGeneration.o
	gcc -o mainDes mainDes.o BitOperations.o keyGeneration.o

mainDes.o: mainDes.c BitOperations.o keyGeneration.o
	gcc -c mainDes.c
keyGeneration.o: keyGeneration.h keyGeneration.c
	gcc -c keyGeneration.c
BitOperations.o: BitOperations.h BitOperations.c
	gcc -c BitOperations.c

clean:
	rm -rf *.o mainDes
