easyml: easyml.o easymlMain.o
	gcc easyml.o easymlMain.o -o easyml -lm

easyml.o: easyml.c given.h
	gcc -Wall -std=c99 -c easyml.c

easymlMain.o: easymlMain.c given.h
	gcc -Wall -std=c99 -c easymlMain.c

clean:
	rm *.o easyml
