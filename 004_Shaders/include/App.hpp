#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <memory>
#include <vector>
#include <random>

#include <glm/glm.hpp>

#include "Renderer.hpp"
class App{
    public:
	App(int width, int height);
	~App();
	void run();
	void onResize(int newWidth, int newHeight);
    private:
	GLFWwindow * window;
	int width;
	int height;
	
	glm::vec2 playerPos{0.f, -0.8f};
	float playerSpeed = 1.f;

	std::unique_ptr<Renderer> renderer;
	void processInput(float dt);
	void render();
};

