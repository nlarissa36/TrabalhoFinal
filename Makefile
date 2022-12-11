all: prog.exe

prog.exe: main.o readPGM.o menu.o quantization.o computeMatrix.o
	gcc -o prog.exe main.o readPGM.o menu.o quantization.o computeMatrix.o

main.o: main.c
	gcc -o main.o -c main.c

readPGM.o: readPGM.c
	gcc -o readPGM.o -c readPGM.c

menu.o: menu.c
	gcc -o menu.o -c menu.c

quantization.o: quantization.c
	gcc -o quantization.o -c quantization.c

computeMatrix.o: computeMatrix.c
	gcc -o computeMatrix.o -c computeMatrix.c

clean:
	rm -f *.o prog.exe
