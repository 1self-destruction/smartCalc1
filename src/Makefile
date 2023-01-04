GCC = gcc -Wall -Werror -Wextra -std=c11
TST_LIB = -lcheck
OS := $(shell uname -s)

ifeq ($(OS),Linux)
		TST_LIB+= -lrt -lm -lpthread -lsubunit
else
	ifeq ($(OS),Darwin)
		TST_LIB+=-lm -lpthread
	endif
endif

all: clean SmartCalc.a install test gcov_report

clean:
	rm -rf *.a && rm -rf *.o *.exe
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov *.html *.css *.cfg
	rm -rf report/ && rm -rf *.out
	rm -rf .clang-format manual
	rm -rf manual

SmartCalc.a: clean
	$(GCC) -c SmartCalc_v1_0.c -o ./SmartCalc_v1_0.o
	ar rcs SmartCalc_v1_0.a SmartCalc_v1_0.o
	ranlib SmartCalc_v1_0.a

dvi:
	makeinfo manual.texi --html
	open ./manual/index.html

install:
	cd SmartCalc && cmake .
	cd SmartCalc && make
	./SmartCalc/smartCalc1

uninstall:
	cd SmartCalc && make clean
	rm -rf SmartCalc/CMakeFiles SmartCalc/cmake_install.cmake SmartCalc/CMakeCache.txt SmartCalc/Makefile
	rm -rf SmartCalc/QCustomPlot-library/*.cmake SmartCalc/QCustomPlot-library/CMakeFiles
	rm -rf SmartCalc/QCustomPlot-library/Makefile

dist:
	cd ../ && tar -czf s21_SmartCalc_v1.0.tgz src

test: SmartCalc.a
	$(GCC) tests.c -L. SmartCalc_v1_0.a $(TST_LIB) -o ./tests.exe
	$(GCC) --coverage tests.c SmartCalc_v1_0.c SmartCalc_v1_0.a -L. SmartCalc_v1_0.a $(TST_LIB) -o ./tests.exe
	./tests.exe

gcov_report: SmartCalc.a test
	gcov -a -f SmartCalc_v1_0.gcda
	gcovr --html-details -o report.html
	open report.html

check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n SmartCalc/*.c
	clang-format -n SmartCalc/*.h
	clang-format -n SmartCalc/*.cpp
	clang-format -n SmartCalc/*.ui
	clang-format -n *.c
	clang-format -n *.h
	cppcheck SmartCalc/*.c
	cppcheck --language=c++ SmartCalc/*.cpp
	cppcheck --language=c++ SmartCalc/*.h
	cppcheck *.c
	cppcheck *.h

correct:
	clang-format -i SmartCalc/*.c
	clang-format -i SmartCalc/*.h
	clang-format -i SmartCalc/*.cpp
	clang-format -i SmartCalc/*.ui
	clang-format -i *.c
	clang-format -i *.h

