# Julian Keller, julian.keller@wsu.edu
# Makefile for dk.c

.SUFFIXES: .c .o
CC = gcc
CCFLAGS = -std=c99 -pedantic -Wall -g
EXEC = dk
OBJS = dk.o
PROJ = dk
TARBALL = ${USER}-${PROJ}.tgz


${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -o ${EXEC} ${OBJS} -lm

.c.o:
	${CC} ${CCFLAGS} -c $<

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${EXEC} ${OBJS}

tarball: clean
	rm -f ${USER}-${PROJ}.tgz
	tar -czf ${USER}-${PROJ}.tgz *

dk.o: dk.c dk.h
