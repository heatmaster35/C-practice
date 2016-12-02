################################
# Name: Leo Gomez              #
# CruzID: legomez              #
# Class: CMPS-12M              #
# Date: Nov 7, 2014            #
# filename: Makefile           #
# Details:makefile for testing #
#  and queue.c                 #
################################

CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wfatal-errors -g
OBJS = queue.o
OUTPUT = queue
HEADERS = minunit.h

${OUTPUT}: ${OBJS}
	${CC} $< -o ${OUTPUT}

%.o: %.c ${HEADERS}
	${CC} -c ${CFLAGS} $<

clean:
	rm -f *.o

spotless: clean
	rm -f ${OUTPUT}

test: ${OUTPUT}
	./${OUTPUT}

.PHONY: clean spotless test

