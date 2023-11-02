CC = g++ -std=c++17
CFLAGS = -Wall -Werror -Wextra
LIBS=-lgtest
SOURCES=s21_matrix_oop.cc
OBJECTS=s21_matrix_oop.o
OS=$(shell uname -s)

all: clean test

s21_matrix_oop.a:
	$(CC) -c $(CFLAGS) $(SOURCES)
	ar rcs s21_matrix_oop.a $(OBJECTS)
	ranlib s21_matrix_oop.a

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*.cc ./*.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) s21_unit_tests.cc s21_matrix_oop.a -o s21_tests $(LIBS)
	./s21_tests

gcov_report: clean
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_unit_tests.cc $(SOURCES) -o s21_tests $(LIBS)
	./s21_tests
	lcov -t "test" -o test.info -c -d . --no-external
	lcov --remove test.info $(shell pwd)/s21_unit_tests.cc -o test.info
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf s21_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report
