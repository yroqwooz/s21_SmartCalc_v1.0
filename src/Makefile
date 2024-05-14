CC = gcc
CFLAGS = -Wall -Wextra -Werror 
APP = build/SmartCalcPR.app
GCOVFLAGS:=-fprofile-arcs -ftest-coverage

LDFLAGS:=-lcheck -fprofile-arcs --coverage -L.
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif



BACKEND_FILES = SmartCalcPR/lib/s21_*.c
BACKEND_FILES_O = *.o
BACKEND_FILES_O_GCOV = gcov_obj/*.o

all: install s21_calc.a test

build: 
	mkdir build
	cd ./build/ && qmake6 ../SmartCalcPR/SmartCalcPR.pro && make first

install: build 
	@mkdir ./C7_SmartCalc_v1
	@cp -rf $(APP) ./C7_SmartCalc_v1

uninstall:
	@rm -rf ./C7_SmartCalc_v1

dist:
	rm -rf Archive_SmartCalcPR_v1.0/
	mkdir Archive_SmartCalcPR_v1.0/
	mkdir Archive_SmartCalcPR_v1.0/src
	cp Makefile SmartCalcPR/*.h SmartCalcPR/*.pro SmartCalcPR/*.cpp SmartCalcPR/*.ui SmartCalcPR/*.user SmartCalcPR/lib/s21*.* Archive_SmartCalcPR_v1.0/src/
	tar cvzf Archive_SmartCalcPR_v1.0.tgz Archive_SmartCalcPR_v1.0/
	rm -rf Archive_SmartCalcPR_v1.0/
dvi:
	@open ../README_RUS.md

check: 
	@cp ../materials/linters/.clang-format .
	@clang-format -n SmartCalcPR/lib/*.c SmartCalcPR/lib/*.h SmartCalcPR/*.cpp
	@clang-format -i SmartCalcPR/lib/*.c SmartCalcPR/lib/*.h SmartCalcPR/*.cpp
	@rm ./.clang-format

s21_calc.a:
	$(CC) $(CFLAGS) -c $(BACKEND_FILES)
	@ar rcs s21_calc.a $(BACKEND_FILES_O)

s21_calc_gcov.a: gcov_obj
	@ar rcs s21_calc_gcov.a $(BACKEND_FILES_O_GCOV)

test: s21_calc_gcov.a 
	$(CC) $(CFLAGS) $(BACKEND_FILES_O_GCOV) SmartCalcPR/tests/tests.c -o test_run $(LDFLAGS)
	./test_run

gcov_report: test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html

gcov_obj: SmartCalcPR/lib/*.c
	mkdir gcov_obj
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c SmartCalcPR/lib/s21_calc.c -o gcov_obj/s21_calc.o
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c SmartCalcPR/lib/s21_list.c -o gcov_obj/s21_list.o

leaks: s21_calc.a
	$(CC) $(CFLAGS) SmartCalcPR/lib/*.c SmartCalcPR/tests/tests.c -o test_run -lcheck -lpthread -lm -D_GNU_SOURCE -lrt -lsubunit
	CK_FORK=no valgrind --leak-check=full --track-origins=yes --log-file="valgrind_log.txt" ./test_run 

clean:
	rm -rf a.out
	rm -rf *.a *.o
	rm -rf *.gcda *.gcno *.info
	rm -rf test report build
	rm -rf C7_SmartCalc_v1
	rm -rf gcov_obj
	rm -rf valgrind_log.txt
	rm -rf test_run
	rm -rf *.tgz
