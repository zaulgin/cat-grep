CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -std=c11
LDFLAGS=-Wall -Wextra -Werror
EXECUTABLE=s21_cat
CATDIR=cat/
SOURCES=$(CATDIR)s21_cat.c $(CATDIR)parsing.c $(CATDIR)cat_functions.c
OBJECTS=$(SOURCES:.c=.o)

all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

$(CATDIR)/%.o: $(CATDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

rebuild: clean all