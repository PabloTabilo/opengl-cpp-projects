# Variables
CXX = g++

SRC = \
	src/main.cpp \
	src/glad.c \
	Linking/lib/stb.cpp

OUT = build/out.exe

# Incluye la carpeta raíz donde están glad, GLFW, stb, glm, etc.
INCLUDE = -ILinking\include
LIBS = -LLinking/lib -lglfw3 -lopengl32 -lgdi32 -ldwmapi
# Flags de compilación
CXXFLAGS = -std=c++17 $(INCLUDE)

# Regla principal
all:
	if not exist build mkdir build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)
	@echo "Compilation Complete. Ejecutando el programa..."
	@$(OUT)

clean:
	del /Q build\*.exe