S21_LIB=s21_decimal.a
PKG_CONFIG?=pkg-config
CC=gcc
CFLAGS=-Wall -Wextra -Werror
CFLAGS_COV?=-fprofile-arcs -ftest-coverage
CFLAGS_TEST?=$(CFLAGS) $(CFLAGS_COV) $(shell $(PKG_CONFIG) --cflags check)
DIR_TEST:=s21_test/
DIR_REPORT:=report/
HEADERS:=$(S21_LIB:a=h) common/s21_arithmetic.h common/s21_getset.h common/s21_scaling.h
OBJS=	s21_addsub.o s21_mul.o s21_div.o\
		s21_from_float_to_decimal.o s21_from_int_to_decimal.o s21_from_decimal_to_float.o s21_from_decimal_to_int.o\
		s21_floor.o s21_round.o s21_truncate.o s21_negate.o\
		s21_is_less.o s21_is_less_or_equal.o s21_is_greater.o s21_is_greater_or_equal.o s21_is_equal.o s21_is_not_equal.o \
		common/s21_arithmetic.o common/s21_getters.o common/s21_scaling.o common/s21_setters.o common/s21_compare.o
OBJS_TEST:=$(OBJS:.o=_cov.o)
EXEC_TEST:=run_test
LIBS_TEST?=$(shell $(PKG_CONFIG) --libs check)

.PHONY: all test gcov_report style clean rebuild

all: clean $(S21_LIB)
	

$(S21_LIB): $(OBJS)
	ar rcs $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

%_cov.o: %.c $(HEADERS)
	$(CC) $(CFLAGS_TEST) -c -o $@ $<

test: clean $(OBJS_TEST)
	ar rcs $(S21_LIB) $(OBJS_TEST)
	$(CC) $(CFLAGS_TEST) -o $(EXEC_TEST) $(DIR_TEST)*.c $(S21_LIB) $(LIBS_TEST)
	./$(EXEC_TEST) ; rm -f $(EXEC_TEST)*.gc?? s21_test*.gc??

gcov_report: clean test
	lcov -c -o s21_test.info -d .
	genhtml -o $(DIR_REPORT) s21_test.info
	rm -f $(OBJS_TEST) $(OBJS_TEST:.o=.gc??)

style:
	cppcheck --enable=all --suppress=missingIncludeSystem . 
	clang-format -n *.c *.h common/*.c common/*.h $(DIR_TEST)*.c $(DIR_TEST)*.h

clean:
	rm -rf $(S21_LIB) $(OBJS) $(OBJS_TEST) *.gc?? common/*.gc?? $(DIR_TEST)*.gc?? $(EXEC_TEST) s21_test.info $(DIR_REPORT)

rebuild: clean all