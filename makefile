all: main.exe

main.exe: mylib.o
	gcc -o main main.c mylib.o

mylib.o: mylib/mylib.c
	gcc -c mylib/mylib.c
	gcc -o main.exe main.c mylib.o

clear:
	rm *.exe
	rm *.o

