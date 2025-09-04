TARGET = exec
SRC = src/main.cpp src/Stickman.cpp

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
# Nota: Las bibliotecas deben ir DESPUÉS de los archivos fuente
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(TARGET)

# Importante: Los archivos fuente primero, luego las bibliotecas
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SFML_LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run