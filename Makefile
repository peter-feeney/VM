SRC_FILES = my-VM.c eval.c IO.c
CC_FLAGS = -Wall -Wextra -g -std=c11
CC = gcc

all:
	${CC} ${SRC_FILES} ${CC_FLAGS} -o VM.x
