CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror
EXECUTABLE=s21_cat
OBJECTS=$(SOURCES:.c=.o)
SOURCES=s21_cat.c parsing.c cat_functions.c cat_flags_struct.h


all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)

