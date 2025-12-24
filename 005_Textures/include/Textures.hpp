// Textures.hpp
#pragma once
#include <iostream>
#include <glad/glad.h>
#include <string>
#include <stb/stb_image.h>

class Textures{
    public:
		Textures(const std::string& path);
		unsigned int id() const {return texture1;}	
    private:
		unsigned int texture1;
		int width, height, nrChannels;
		unsigned char *data;
};
