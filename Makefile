# Copyright 2018 Grama Nicolae

CC = gcc
CFLAGS = -lm -Wall -Wextra -std=c99
EXE = gigel
SOURCE = main.c

# compilarea programului
build: $(SOURCE)
		$(CC) -o $(EXE) $^ $(CFLAGS)

# ruleaza programul
run: build
		./$(EXE)

# arhiveaza tema
pack:
	zip -FSr 312CA_GramaNicolae_Tema2.zip README Makefile *.c *.h
	
.PHONY:pack

# sterge executabilul
clean:
	rm -f $(EXE)

.PHONY:clean

# face coding-style automat, la standardul google, cu o mica modificare
# (4 spatii in loc de 2 la alineate)
beautify: 
	clang-format -i -style=file $(SOURCE)

.PHONY:beautify

# descarca arhiva de teste si o pregateste
update:
	wget https://ocw.cs.pub.ro/courses/_media/programare/teme_2018/check_gigel.zip
	unzip check_gigel.zip -d ./checker
	rm -f check_gigel.zip*

.PHONY:update

# verifica doar coding-style
styleCheck: 
	-python ./checker/cs.py $(SOURCE)

.PHONY: styleCheck

# verifica toata tema, cu ajutorul checkerului
check:
	cp README.md ./checker/README.md
	cp main.c ./checker/$(SOURCE)
	cp Makefile ./checker/Makefile
	-bash ./checker/check.sh
	rm -f ./checker/README.md
	rm -f ./checker/$(SOURCE)
	rm -f ./checker/Makefile
	
.PHONY: check