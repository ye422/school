cc = gcc
object = blackcow.o turtle.o dog.o main.o
target = main

$(target) : $(object) 
	$(cc) -o $(target) $(object)

%.o : $.c 
	$(cc) -c -o $@ $<

.PHONY : clean
clean : 
	rm $(object) $(target)
