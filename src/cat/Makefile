CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror

EXECUTABLE=s21_cat
EXECUTABLE_TEST=s21_cat_test

SOURCES=s21_cat.c cat_parsing.c cat_functions.c

OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean rebuild

all: $(EXECUTABLE) $(EXECUTABLE_TEST)

$(EXECUTABLE_TEST):
	$(CC) $(LDFLAGS) s21_cat_test.c -o s21_cat_test

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE_TEST)

rebuild: clean all