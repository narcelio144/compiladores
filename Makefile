CC=g++
CFLAGS=-lstdc++
TARGET=ss_compiler
SOURCE= src/analisador_lexico.cpp src/main.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)

clean:
	$(RM) $(TARGET)
