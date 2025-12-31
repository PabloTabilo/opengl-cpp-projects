// App.cpp
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

static void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if(app){
	app->onMouseMove(xpos, ypos);
    }
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

    // Z-buffer
    glEnable(GL_DEPTH_TEST);

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    // ocultar cursor y capturar
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	render(dt);

	glfwSwapBuffers(window);
	glfwPollEvents();
    }
}

void App::onResize(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
    renderer->onResize(newWidth, newHeight);
}

void App::onMouseMove(double xpos, double ypos){
    if(firstMouse){
	lastX = xpos;
	lastY = ypos;
	firstMouse = false;
    }
    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos);

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void App::processInput(float deltaTime){
    camera.MovementSpeed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? sprintSpeed : baseSpeed;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
	glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
	camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
	camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
	camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
	camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
	camera.Position += camera.WorldUp * camera.MovementSpeed * deltaTime;
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
	camera.Position -= camera.WorldUp * camera.MovementSpeed * deltaTime;
    }
}
void App::render(float dt){
    renderer->renderScene(camera);
}
