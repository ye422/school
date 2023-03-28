target = a.out
obj = main.o str.o
hdr = str.h

$(target) : $(obj)
	g++ -o $(target) $(obj) 

$(obj) : $(hdr)

.PHONY : clean

clean : 
	rm *.o $(target)
