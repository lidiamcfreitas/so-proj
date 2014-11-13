CC = gcc
LEITOR_PAI_1_FILES = leitor_pai_1.c
LEITOR_PAI_1_EXE = leitor_pai_1
LEITOR_FILHO_1_FILES = leitor_filho_1.c
LEITOR_FILHO_1_EXE = leitor_filho_1
LEITOR_2_FILES = leitor_2.c
LEITOR_2_EXE = leitor_2
LEITOR_3_FILES = leitor_3.c
LEITOR_3_EXE = leitor_3
THREAD_FLAGS = -pthread


all:build1 build2 build3 build4

build1: $(LEITOR_PAI_1_FILES);$(CC) -o $(LEITOR_PAI_1_EXE) $(LEITOR_PAI_1_FILES)

build2: $(LEITOR_FILHO_1_FILES);$(CC) -o $(LEITOR_FILHO_1_EXE) $(LEITOR_FILHO_1_FILES) 

build3: $(LEITOR_2_FILES);$(CC) -o $(LEITOR_2_EXE) $(LEITOR_2_FILES) $(THREAD_FLAGS)

build4: $(LEITOR_3_FILES);$(CC) -o $(LEITOR_3_EXE) $(LEITOR_3_FILES) $(THREAD_FLAGS)

clean:rm -f *.o core

rebuild: clean build
