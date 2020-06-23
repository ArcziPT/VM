CC = g++
TARGET = vm

IDIR = -I$(dir $(abspath $(lastword $(MAKEFILE_LIST))))

SRC = $(shell find -name "*.cpp")

CFLAGS = -Wall
LIBS = -pthread -lSDL2 -lSDL2_ttf

all: 
	$(CC) $(IDIR) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET) 

debug:
	$(CC) -g -D DEBUG_LOG $(IDIR) $(CFLAGS) $(SRC) $(LIBS) -o $(TARGET)d
