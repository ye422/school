cc = gcc
object = main.o separate.o count.o print.o
header = head.h
target = main

$(target) : $(object)
	$(cc) -o $(target) $(object)
	
%.o : %.c 
	$(cc) -c -o $@ $<

$(object) : $(header)

.PHONY : clean

clean : 
	rm $(object) $(target)
