
all: sim.h
	gcc -o main Compiler.c Linked_list.c
	g++ -o decorder decorder.cpp
	g++ -o asm asm.cpp

clean:
	del out.txt 
	del asm.out
	 

run:
	main.exe
	asm.exe 124
	decorder.exe asm.out 124
