CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror

EXECUTABLE=s21_grep
EXECUTABLE_TEST=s21_grep_test

SOURCES=s21_grep.c grep_parsing.c grep_functions.c

OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean rebuild

all: $(EXECUTABLE) $(EXECUTABLE_TEST)

$(EXECUTABLE_TEST):
	$(CC) $(LDFLAGS) s21_grep_test.c -o s21_grep_test

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(EXECUTABLE_TEST) *.diff *.log

rebuild: clean all