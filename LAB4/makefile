CC = gcc
READER_FILES = reader1.c
READER_EXE = reader
EXECUTABLE_FILES = wchild.c
EXECUTABLE_EXE = wchild
READER1_FILES = LEITOR-PAI.c
READER1_EXE = LEITOR
WRITER_FILES = writer.c
WRITER_EXE = writer

all:build1 build2 build3 build4

build1: $(READER_FILES);$(CC) -o $(READER_EXE) $(READER_FILES)

build2: $(READER1_FILES);$(CC) -o $(READER1_EXE) $(READER1_FILES)

build3: $(EXECUTABLE_FILES);$(CC) -o $(EXECUTABLE_EXE) $(EXECUTABLE_FILES)

build4: $(WRITER_FILES);$(CC) -o $(WRITER_EXE) $(WRITER_FILES)

clean:rm -f *.o core

rebuild: clean build
