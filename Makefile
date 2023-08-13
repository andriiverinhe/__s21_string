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

test: obj
	$(FLAGS) $(FUNC_FILES_O) tests/test_str_char.c $(CHECKFLAGS) -o ./exec/str_char_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_int.c $(CHECKFLAGS) -o ./exec/int_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_u_int.c $(CHECKFLAGS) -o ./exec/u_int_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_o.c $(CHECKFLAGS) -o ./exec/o_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_x.c $(CHECKFLAGS) -o ./exec/x_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_p.c $(CHECKFLAGS) -o ./exec/p_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_f.c $(CHECKFLAGS) -o ./exec/f_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_e.c $(CHECKFLAGS) -o ./exec/e_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_g.c $(CHECKFLAGS) -o ./exec/g_test
	$(FLAGS) $(FUNC_FILES_O) tests/test_n.c $(CHECKFLAGS) -o ./exec/n_test
	./exec/str_char_test
	./exec/int_test
	./exec/u_int_test
	./exec/o_test
	./exec/x_test
	./exec/p_test
	./exec/f_test
	./exec/g_test
	./exec/e_test
	./exec/n_test

clean:
	rm -rf *.o
	rm -rf ./exec/*
	rm -rf ./obj
