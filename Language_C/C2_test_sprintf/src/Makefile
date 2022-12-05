CC := gcc

# отредктировать флаги (для библиотеки и для тестирования)
C_FLAG := -c -g # !!! убрать перед финальным заливом на develop
G_FLAG := -g
CFLAGS := -Wall -Werror -Wextra -std=c11

# ifeq ($(shell uname), Darwin)
LIB_FLAG :=
ifeq ($(shell uname), Linux)
LIB_FLAG := -lm
# else
# LIB_FLAG :=
endif

all: for_tests

for_tests: for_test.o s21_memcpy.o s21_memmove.o s21_memset.o s21_strcat.o s21_sprintf.o s21_strchr.o s21_strcpy.o s21_strlen.o
	$(CC) for_test.o s21_memcpy.o s21_memmove.o s21_memset.o s21_strcat.o s21_sprintf.o s21_strchr.o s21_strcpy.o s21_strlen.o -o for_test $(LIB_FLAG)

for_test.o: for_test.c s21_string.h s21_sprintf.h
	$(CC) $(C_FLAG) $(CFLAGS) for_test.c

s21_memcpy.o: s21_memcpy.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_memcpy.c

s21_memmove.o: s21_memmove.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_memmove.c

s21_memset.o: s21_memset.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_memset.c

s21_strcat.o: s21_strcat.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strcat.c

s21_sprintf.o: s21_sprintf.c s21_string.h s21_sprintf.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_sprintf.c

s21_strchr.o: s21_strchr.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strchr.c

s21_strcpy.o: s21_strcpy.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strcpy.c

s21_strlen.o: s21_strlen.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strlen.c

.PHONY: clean clean_res clean_all

clean:
	rm -rf *.o

clean_res:
	rm -rf for_test

clean_all: clean clean_res

rebuild: clean all
