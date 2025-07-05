CFLAGS = -Wall -Wextra -Werror -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS:=-lcheck -lgcov -fprofile-arcs --coverage
ifeq ($(shell uname), Linux)
LDFLAGS +=-pthread -lcheck_pic -lrt -lm -lsubunit
endif

SRC := s21_string.c s21_sprintf.c

OBJ_LIBRARY := $(patsubst %.c, %.o, $(SRC))

.PHONY: all gcov_report clean rebuild

%.o: %.c s21_string.h
	gcc $(CFLAGS) -c $< -o $@

all: s21_string.a gcov_report test

s21_string.a: $(OBJ_LIBRARY) s21_string.h
	ar rsc s21_string.a $(OBJ_LIBRARY)

test: s21_string.a s21_string_test.c
	gcc $(CFLAGS) s21_string_test.c s21_string.a -o test.out $(LDFLAGS)
	./test.out

gcov_report: s21_string_test.c
	gcc $(GCOVFLAGS) s21_string_test.c $(SRC) -o report.out $(LDFLAGS)
	./report.out
	lcov -t "gcov_report" -o report.info -c -d .
	genhtml -o ./report report.info

rebuild: clean all

clean:
	@rm -f *.out
	@rm -f *.o
	@rm -rf report
	@rm -f *.a
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f *.info
