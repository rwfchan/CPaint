paint.out: main.o paint.o
	gcc -g -Wall -Werror -o paint.out main.o paint.o
main.o: main.c paint.h
	gcc -g -Wall -Werror -c main.c
paint.o: paint.c paint.h
	gcc -g -Wall -Werror -c paint.c
clean:
	rm -fr *.o paint.out