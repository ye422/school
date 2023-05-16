cc = gcc
cflags = -W -g
objects = String_Manipulation.o main.o Output.o
header = Header.h
target = main

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)

$(objects) : $(header)

.PHONY : clean
clean :
	rm $(objects) $(target) 
