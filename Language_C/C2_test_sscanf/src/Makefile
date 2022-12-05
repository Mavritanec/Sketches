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

all: test_sscanf

test_sscanf: s21_memcpy.o s21_memmove.o s21_strcat.o s21_strlen.o s21_sscanf.o test_sscanf.o
	$(CC) s21_memcpy.o s21_memmove.o s21_strcat.o s21_strlen.o s21_sscanf.o test_sscanf.o -o test_sscanf $(LIB_FLAG)

s21_memcpy.o: s21_memcpy.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_memcpy.c

s21_memmove.o: s21_memmove.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_memmove.c

s21_strcat.o: s21_strcat.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strcat.c

s21_strlen.o: s21_strlen.c s21_string.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_strlen.c

s21_sscanf.o: s21_sscanf.c s21_string.h s21_sscanf.h
	$(CC) $(C_FLAG) $(CFLAGS) s21_sscanf.c

test_sscanf.o: test_sscanf.c s21_string.h s21_sscanf.h
	$(CC) $(C_FLAG) $(CFLAGS) test_sscanf.c

.PHONY: clean clean_res clean_all

clean:
	rm -rf *.o

clean_res:
	rm -rf test_sscanf

clean_all: clean clean_res

rebuild: clean_all all
