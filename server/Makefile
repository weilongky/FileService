server: main.o tcpip.o user.o file_server.o 
	gcc main.c tcpip.c user.c file_server.c -o server -lsqlite3
main.o: main.c head.h
	gcc -c main.c -o main.o
tcpip.o:tcpip.c head.h
	gcc -c tcpip.c -o tcpip.o
user.o:user.c head.h
	gcc -c user.c -o user.o
file_server.o:file_server.c head.h
	gcc -c file_server.c -o file_server.o
.PHONY:clean
clean:
	rm *.o server
