CC=g++
CFLAGS=-std=c++17 
LIBS=-lgtest

all: clean test

style:
	cp ./../materials/linters/.clang-format .
	clang-format -n ./*/*.tpp ./*/*.h ./*.tpp ./*.h

valgrind: test
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./s21_tests

test: clean
	$(CC) $(CFLAGS) s21_unit_tests.cc -o s21_tests $(LIBS)
	./s21_tests

gcov_report: clean
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage s21_unit_tests.cc -o s21_tests $(LIBS)
	./s21_tests
	lcov -t "test" -o test.info -c -d . --no-external
	lcov --remove test.info $(shell pwd)/s21_unit_tests.cc -o test.info
	genhtml -o report test.info
	open ./report/index.html

clean:
	rm -rf .clang-format
	rm -rf s21_tests *.o *.a
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf report
