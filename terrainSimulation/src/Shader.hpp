#pragma once
#include <string>

// Compila un shader desde archivo
unsigned int compileShaderFromFile(const std::string& path, unsigned int type);

// Crea un programa (vertex + fragment)
unsigned int createShaderProgram(const std::string& vertPath, const std::string& fragPath);
