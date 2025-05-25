# Variables
CXX = g++

SRC = \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/main.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/Shader.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/world/Chunk.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/world/Block.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/io/Camera.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/io/Mouse.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/io/Keyboard.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/world/HeightMapGeneration.cpp \
	BuildAnAutoGenerateTerrainMinecraftStyle/src/glad.c \
	Linking/lib/stb.cpp

OUT = build/terrain.exe

# Incluye la carpeta raíz donde están glad, GLFW, stb, glm, etc.
INCLUDE = -ILinking\include
LIBS = -LLinking/lib -lglfw3 -lopengl32 -lgdi32 -ldwmapi
# Flags de compilación
CXXFLAGS = -std=c++17 $(INCLUDE)

# Regla principal
all:
	if not exist build mkdir build
	$(CXX) $(SRC) -o $(OUT) $(CXXFLAGS) $(LIBS)
	@echo "Compilación completada. Ejecutando el programa..."
	@$(OUT)

clean:
	del /Q build\*.exe