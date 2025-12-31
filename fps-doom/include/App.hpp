// App.hpp
#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <memory>
#include <vector>
#include <random>

#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Camera.hpp"

class App{
    public:
	App(int width, int height);
	~App();
	void run();
	void onResize(int newWidth, int newHeight);

	void onMouseMove(double xpos, double ypos);
    private:
	GLFWwindow * window;
	int width;
	int height;

	Camera camera;
	float baseSpeed = 5.0f;
	float sprintSpeed = 10.0f;

	bool firstMouse = true;
	double lastX = 0.0;
	double lastY = 0.0;
	
	std::unique_ptr<Renderer> renderer;
	void processInput(float dt);
	void render(float dt);
};

