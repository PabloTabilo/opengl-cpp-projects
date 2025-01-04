// BuildAnAutoGenerateTerrainMinecraftStyle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "io/keyboard.h"
#include "io/Mouse.h"
#include "io/camera.h"

unsigned int SCR_WIDTH = 1280;
unsigned int SCR_HEIGHT = 720;

const char* rem = "remember that i hate my life!";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, double dt);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0, 3.0));

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    std::cout << rem << std::endl;

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, rem, NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, Keyboard::keyCallback);

    glfwSetCursorPosCallback(window, Mouse::cursorPosCallback);
    glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
    glfwSetScrollCallback(window, Mouse::mouseWheelCallback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Shader shader("assets/vertex_core.glsl", "assets/fragment_core.glsl");

    glEnable(GL_DEPTH_TEST);

	float vertices[] = {
		// positions          // texCoords
		// Back face
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
		0.5f, -0.5f, -0.5f,  0.25f, 0.0f, // bottom-right
		0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
		0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
	   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
	   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left

	   // Front face
	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
	   0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
	   0.5f,  0.5f,  0.5f,  0.25f, 1.0f, // top-right
	   0.5f,  0.5f,  0.5f,  0.25f, 1.0f, // top-right
	  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
	  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left

	  // Left face
	 -0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-right
	 -0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-left
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-left
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-left
	 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-right
	 -0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-right

	 // Right face
	 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-left
	 0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-right
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-right
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
	 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-left

	 // Bottom face
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // top-left
	 0.5f, -0.5f, -0.5f,  0.25f, 1.0f, // top-right
	 0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
	 0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // top-left

	// Top face
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
	0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
	0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
	0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f   // top-left
	};


	// world space positions of our cubes
	//glm::vec3 cubePositions[] = {
	//	glm::vec3(0.0f,  0.0f,  0.0f),
	//	glm::vec3(0.0f,  0.0f, -5.0f),
		//glm::vec3(-1.5f, -2.2f, -2.5f),
		//glm::vec3(-3.8f, -2.0f, -12.3f),
		//glm::vec3(2.4f, -0.4f, -3.5f),
		//glm::vec3(-1.7f,  3.0f, -7.5f),
		//glm::vec3(1.3f, -2.0f, -2.5f),
		//glm::vec3(1.5f,  2.0f, -2.5f),
		//glm::vec3(1.5f,  0.2f, -1.5f),
		//glm::vec3(-1.3f,  1.0f, -1.5f)
	//};
	unsigned int n = 10, m = 10;
	std::vector<glm::vec3> cubePositions;
	float newXpos = 0.0f;
	float gap = 1.1f;
	float prevPos = 2.0f;
	float newPos;
	for (unsigned int i = 0; i < n; i++) {
		prevPos = 2.0f;
		for (unsigned int j = 0; j < m; j++) {
			newPos = prevPos - gap;
			cubePositions.push_back(glm::vec3(newXpos, 0.0f, newPos));
			prevPos = newPos;
		}
		newXpos += gap;
	}
	

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind VAO
	glBindVertexArray(VAO);
	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Cube
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	stbi_set_flip_vertically_on_load(true);

	// load image
	int width, height, nChannels;
	unsigned char* data = stbi_load("assets/tiles.png", &width, &height, &nChannels, 0);
	std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << nChannels << std::endl;
	if (data) {
		if (nChannels == 3) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else if (nChannels == 4) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "fail to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader.activate();
	shader.setInt("texture1", 0);



    while (!glfwWindowShouldClose(window))
    {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

        processInput(window, deltaTime);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.activate();

		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(camera.zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		view = camera.getViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		glBindVertexArray(VAO);

		for (auto cubePos : cubePositions) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePos);
			//float angle = ((float)glfwGetTime() / -100.00f) + 20.0f * i;
			//model = glm::rotate(model, sin((float)glfwGetTime() * glm::radians(50.0f)), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		/*
		for (unsigned int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			//float angle = ((float)glfwGetTime() / -100.00f) + 20.0f * i;
			model = glm::rotate(model, sin((float)glfwGetTime() * glm::radians(50.0f)), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		*/

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

void processInput(GLFWwindow* window, double dt)
{
	if (Keyboard::key(GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(window, true);
	}

	//move camera
	if (Keyboard::key(GLFW_KEY_W)) {
		camera.updateCameraPos(CameraDirection::FORWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		camera.updateCameraPos(CameraDirection::BACKWARD, dt);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		camera.updateCameraPos(CameraDirection::RIGHT, dt);
	}
	if (Keyboard::key(GLFW_KEY_A)) {
		camera.updateCameraPos(CameraDirection::LEFT, dt);
	}
	if (Keyboard::key(GLFW_KEY_SPACE)) {
		camera.updateCameraPos(CameraDirection::UP, dt);
	}
	if (Keyboard::key(GLFW_KEY_LEFT_SHIFT)) {
		camera.updateCameraPos(CameraDirection::DOWN, dt);
	}

	double dx = Mouse::getDX(), dy = Mouse::getDY();

	if (dx != 0 || dy != 0) {
		camera.updateCameraDirection(dx * 0.21, dy * 0.21);
	}

	double scrollDy = Mouse::getScrollDY();
	if (scrollDy != 0) {
		camera.updateCameraZoom(scrollDy);
	}

}
