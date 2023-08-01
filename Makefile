FLAGS= gcc -Wall -Werror -Wextra -g
FUNC_FILES_C = *.c
FUNC_FILES_O = *.o
FILE = main
LIBS = -lcheck -lsubunit -lm -lgcov
CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS = -fprofile-arcs -ftest-coverage
GLFLAGS = --coverage

all: sprintf

obj:
	$(FLAGS) -lm -c $(FUNC_FILES_C) 

sprintf: obj
	$(FLAGS) $(FUNC_FILES_O) -lm -o main

test: obj
	$(FLAGS) $(FUNC_FILES_O) tests/test_str_char.c $(CHECKFLAGS) -o ./exec/str_char_test
	exec/*test

clean:
	rm -rf *.o
	rm -rf ./exec/*
	rm main
