
# All Targets
all: myshell

# Tool invocations
myshell: myshell.o LineParser.o 
	gcc -g -Wall -o myshell myshell.o LineParser.o 

# Depends on the source and header files
LineParser.o: LineParser.c LineParser.h
	gcc -g -Wall -ansi -c LineParser.c -o LineParser.o

myshell.o: myshell.c
	gcc -g -Wall -ansi -c myshell.c -o myshell.o

#tell make that "clean" is not a file name!
.PHONY: clean run

#Clean the build directory	
clean: 
	rm -vf myshell *.o
run:
	./myshell
