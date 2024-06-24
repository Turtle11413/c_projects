CC=gcc
FLAGS=-Wall -Wextra -Werror
LIBS=-lm -lcheck

SRC=$(wildcard ./function_files/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

TEST_SRC=$(wildcard ./tests/*.c)
TEST_OBJ=$(patsubst %.c,%.o,$(TEST_SRC))

all: clean s21_matrix.a test

debug: DEBUGFLAGS=-g -DDEBUG
debug: build_main

clang:
	clang-format --style=GOOGLE -n *.h
	clang-format --style=GOOGLE -n function_files/*.c
	clang-format --style=GOOGLE -n tests/*.c

s21_matrix.a: ${OBJ}
	ar rcs s21_matrix.a $^

test.a: ${TEST_OBJ} s21_matrix.a
	ar rcs test.a $^

build_main: s21_matrix.a
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(GCOVFLAGS) $(LIBS) main.c -L. s21_matrix.a -o main

main: build_main
	./main

build_test: s21_matrix.a test.a
	$(CC) $(DEBUGFLAGS) $(GCOVFLAGS) $(LIBS) tests/s21_tests.c -L. test.a -L. s21_matrix.a -o test

test: build_test
	./test

./tests/%.o: ./tests/%.c
	$(CC) $(DEBUGFLAGS) $(GCOVFLAGS) $(LIBS) -c $^ -o $@

./function_files/%.o: ./function_files/%.c
	$(CC) $(FLAGS) $(DEBUGFLAGS) $(GCOVFLAGS) $(LIBS) -c $^ -o $@

clean:
	rm -rf *.a
	rm -rf *.o
	rm -rf function_files/*.o
	rm -rf function_files/*.gcda
	rm -rf function_files/*.gcno
	rm -rf tests/*.o
	rm -rf tests/*.gcda
	rm -rf tests/*.gcno
	rm -rf a.out
	rm -rf *.dSYM
	rm -rf *.out
	rm -rf test
	rm -rf main
	rm -rf gcov_report
	rm -rf *.info
	rm -rf *.gcda
	rm -rf *.gcno

gcov_report: GCOVFLAGS = -lcheck --coverage
gcov_report: DEBUGFLAGS = -g
gcov_report: test
gcov_report:
	geninfo ./ -b ./ -o ./coverage.info
	genhtml coverage.info -o gcov_report
	xdg-open gcov_report/index.html

