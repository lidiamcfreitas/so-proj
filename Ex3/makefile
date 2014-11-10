CC = gcc
READER_FILES = reader.c
READER_EXE = reader
EXECUTABLE_FILES = wchild.c
EXECUTABLE_EXE = wchild
WRITER_FILES = writer.c
WRITER_EXE = writer

all:build1 build2 build3

build1: $(READER_FILES);$(CC) -o $(READER_EXE) $(READER_FILES)

build2: $(EXECUTABLE_FILES);$(CC) -o $(EXECUTABLE_EXE) $(EXECUTABLE_FILES)

build3: $(WRITER_FILES);$(CC) -o $(WRITER_EXE) $(WRITER_FILES)

clean:rm -f *.o core

rebuild: clean build
