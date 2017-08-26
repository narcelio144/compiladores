CC=g++
CFLAGS=-lstdc++ -std=c++11 -g
TARGET=ss_compiler
SOURCE= src/analisador_lexico.cpp src/main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET)
