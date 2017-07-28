CC       = gcc
TARGET   = sorter
CFLAGS   = -Wall -Werror -Wextra -pedantic -std=c99
SOURCES  = array_helpers.c sort.c
HEADERS  = array_helpers.h sort.h
OBJECTS  = $(SOURCES:.c=.o)
INPUT    = input/unsorted-100.in

$(TARGET) :
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) main.c

.PHONY : run indent clean

run : $(TARGET)
	./$(TARGET) $(INPUT)

indent :
	mkdir _original _indent
	cp $(SOURCES) main.c $(HEADERS) _original
	cp $(SOURCES) main.c $(HEADERS) _indent
	indent -kr -nut -brf -cli4 -l79 _indent/*
	meld _original _indent &

clean :
	rm -f $(TARGET) $(OBJECTS)
	rm -rf _original _indent
	rm -f *.c~ *.h~
