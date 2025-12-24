#include "App.hpp"
#include <iostream>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    App* app = reinterpret_cast<App*>(glfwGetWindowUserPointer(window));
    if(app){
        //app->m_renderer.resize(width, height);
    }
}

App::App(int windowWidth, int windowHeight, int gridWidth, int gridHeight)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight),
      m_grid(gridWidth, gridHeight)
{
    if(!glfwInit()){
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(windowWidth, windowHeight, "Grid Toggle", nullptr, nullptr);
    if(!m_window){
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    glViewport(0, 0, windowWidth, windowHeight);
    m_renderer = std::make_unique<Renderer>(gridWidth, gridHeight);
}

App::~App()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void App::processInput()
{
    if(glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(m_window, true);
    }
    int state = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    m_leftMouseDown = (state == GLFW_PRESS);
}

void App::handleMouse() {
    if (!m_leftMouseDown) return;

    double mouseX, mouseY;
    glfwGetCursorPos(m_window, &mouseX, &mouseY);

    double nx = mouseX / m_windowWidth;
    double ny = mouseY / m_windowHeight;

    int gx = static_cast<int>(nx * m_grid.getWidth());
    int gy = static_cast<int>((1.0 - ny) * m_grid.getHeight());

    // Evitar toggle repetido en el mismo pixel durante el mismo drag
    if (gx == m_lastCellX && gy == m_lastCellY) {
        return;
    }

    m_lastCellX = gx;
    m_lastCellY = gy;

    m_grid.toggleCell(gx, gy);
    //m_grid.setCell(gx, gy, true);  // pintar ON
}


void App::run()
{
    std::vector<uint8_t> colorBuffer;

    while(!glfwWindowShouldClose(m_window)){
        processInput();
        handleMouse();
    
        m_grid.buildColorBuffer(colorBuffer);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_renderer->render(colorBuffer);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}