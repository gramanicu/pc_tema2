# Copyright 2018 Grama Nicolae

CC = gcc
CFLAGS = -lm -Wall -Wextra -std=c99
EXE = gigel
SOURCE = main.c

build: $(SOURCE)
		$(CC) -o $(EXE) $^ $(CFLAGS)

# run: build - Ii face si build
run:
		./$(EXE)

# make zip with my homework
pack:
	zip -FSr 312CA_GramaNicolae_Tema2.zip README Makefile *.c *.h
	
.PHONY:pack


clean:
	rm -f $(EXE)

.PHONY:clean

beautify: 
	clang-format -i -style=Google $(SOURCE)

.PHONY:beautify
	
update:
	wget https://ocw.cs.pub.ro/courses/_media/programare/teme_2018/check_gigel.zip
	unzip check_gigel.zip -d /checker

.PHONY: update