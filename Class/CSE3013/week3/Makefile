TARGET = main
OBJS = main.o array.o rangearray.o
HEADERS = Array.h RangeArray.h

$(TARGET): $(OBJS)
	g++ -o $(TARGET) $(OBJS)

$(OBJS): $(HEADERS)

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
