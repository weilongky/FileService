client: main.o tcpip.o user.o file.o show.o
	gcc main.c tcpip.c user.c file.c show.c -o client
main.o: main.c head.h
	gcc -c main.c -o main.o
tcpip.o:tcpip.c head.h
	gcc -c tcpip.c -o tcpip.o
user.o:user.c head.h
	gcc -c user.c -o user.o
file.o:file.c head.h
	gcc -c file.c -o file.o
show.o:show.c head.h
	gcc -c show.c -o show.o
.PHONY:clean
clean:
	rm *.o 
