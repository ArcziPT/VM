CC = g++
TARGET = vm

IDIR = -I$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC = $(shell find -name "*.cpp" -not -path "./tests/*" -not -path "./vm_main/*")
TEST_SRC = $(shell find -name "*.cpp" -path "./tests/*")

CFLAGS = -Wall
LIBS = -pthread -lSDL2 -lSDL2_ttf

TEST_LIBS = -lgtest

all: 
	$(CC) $(IDIR) $(CFLAGS) $(SRC) ./vm_main/main.cpp $(LIBS) -o $(TARGET) 

test:
	$(CC) $(IDIR) $(CFLAGS) $(SRC) $(TEST_SRC) $(LIBS) $(TEST_LIBS) -o $(TARGET)_test

debug:
	$(CC) -g -D DEBUG_LOG $(IDIR) $(CFLAGS) $(SRC) ./vm_main/main.cpp $(LIBS) -o $(TARGET)_debug
