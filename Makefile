# Copyright 2018 Grama Nicolae

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
EXE = gigel
SOURCE = main.c

build: $(SOURCE)
		$(CC) -o $(EXE) $^ $(CFLAGS)

# run: build - Ii face si build
run:
		./$(EXE)

# make zip with my homework
# pack:
#        zip -FSr homework_template.zip README Makefile *.c *.h

clean:
	rm -f $(EXE)
                               