CC = gcc
READER_FILES = reader.c
READER_EXE = reader
WRITER_FILES = writer.c
WRITER_EXE = writer

all:build1 build2

build1: $(READER_FILES);$(CC) -o $(READER_EXE) $(READER_FILES)

build2: $(WRITER_FILES);$(CC) -o $(WRITER_EXE) $(WRITER_FILES)

clean:rm -f *.o core

rebuild: clean build
