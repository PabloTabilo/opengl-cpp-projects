#include "App.hpp"
#include <iostream>
#include <algorithm>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if(app){
	app->onResize(width, height);
    }
    glViewport(0,0,width, height);
}

App::App(int width, int height) : width(width), height(height) {
    if(!glfwInit()){
	throw std::runtime_error("Fail to init GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, "OpenGL app :)", nullptr, nullptr);

    if(!window){
	glfwTerminate();
	throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
	throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    renderer = std::make_unique<Renderer>(width, height);
}

App::~App(){
    if(window){
	glfwDestroyWindow(window);
	window = nullptr;
    }
    glfwTerminate();
}

void App::run(){

    double last = glfwGetTime();

    while(!glfwWindowShouldClose(window)){
	glClear(GL_COLOR_BUFFER_BIT);
	
	double curr = glfwGetTime();
	float dt = static_cast<float>(curr - last);
	last = curr;
	processInput(dt);
	render();

	glfwSwapBuffers(window);
	glfwPollEvents();
    }
}

void App::onResize(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
    renderer->onResize(newWidth, newHeight);
}

void App::processInput(float deltaTime){
    float step = playerSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
	glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
	playerPos.y += step;
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
	playerPos.y -= step;
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
	playerPos.x -= step;
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
	playerPos.x += step;
    }
}
void App::render(){
    renderer->clear();
    float timeValue = glfwGetTime();
    float greenVal = (sin(timeValue) / 2.0f) + 0.5f;
    renderer->drawTriangle(
	playerPos,
	glm::vec2(1.f, 1.f),
	glm::vec3(0.f, greenVal, 0.f)
	    );
}
