animalml: animalml.o animalmlMain.o
	gcc animalml.o animalmlMain.o -o animalml -lm

animalml.o: animalml.c given.h
	gcc -Wall -std=c99 -c animalml.c

animalmlMain.o: easymlMain.c given.h
	gcc -Wall -std=c99 -c animalmlMain.c

clean:
	rm *.o animalml
