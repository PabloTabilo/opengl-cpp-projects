# Variables
CXX = g++

SRC := $(wildcard src/*.cpp src/*.c)

OUT = build/app.exe

# Incluye la carpeta raíz donde están glad, GLFW, stb, glm, etc.
INCLUDE = -Iinclude
LIBS = -Llib -lglfw3 -lopengl32 -lgdi32 -ldwmapi
# Flags de compilación
CXXFLAGS = -std=c++17 $(INCLUDE) -Wall -Wextra

# Regla principal
all:
	if not exist build mkdir build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)
	@echo "Compilation Complete. Ejecutando el programa..."
	@$(OUT)

clean:
	del /Q build\*.exe