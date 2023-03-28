target = main
obj1 = main.o
obj2 = array.o
obj3 = rangearray.o
header1 = Array.h
header2 = RangeArray.h

$(target) : $(obj1) $(obj2) $(obj3)
	g++ -o $(target) $(obj1) $(obj2) $(obj3)

$(obj1) : $(header1) $(header2)

$(obj2) : $(header1)

$(obj3) : $(header2)

.PHONY : clean

clean : 
	rm *.o $(target)
