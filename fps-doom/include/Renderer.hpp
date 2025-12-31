// Renderer.hpp
#pragma once

#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "Textures.hpp"
#include "Shader.hpp"
#include "Camera.hpp"

#include <vector>

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
	void renderScene(const Camera& camera);
	void renderScene2(const Camera& camera);
	void drawCube(const glm::mat4& model);
    private:
	int width, height;
	unsigned int vao = 0, vbo = 0, ebo = 0;
	unsigned int cubeVAO = 0, cubeVBO = 0;
	Shader shader;
	Textures tex;
	void initQuad();
	void initCube();

	int mx;
	int N;
	int M;
	void generateMaze();
	std::vector<std::vector<bool>> positions;
};
