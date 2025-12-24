// Renderer.hpp
#pragma once

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Textures.hpp"
#include "Shader.hpp"

class Renderer{
    public:
		Renderer(int width, int height);
		~Renderer();
		void clear();
		void onResize(int newWidth, int newHeight);
		void drawTriangle(
			const glm::vec2& pos,
			const glm::vec2& scale,
			const glm::vec3& color
			);
		void drawSquare(const glm::vec2& pos);
    private:
		int width, height;
		unsigned int vao = 0, vbo = 0, ebo = 0;
		Shader shader;
		Textures tex;
};
