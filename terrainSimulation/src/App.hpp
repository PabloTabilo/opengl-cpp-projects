#pragma once

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <memory>

#include "Grid.hpp"
#include "Renderer.hpp"



class App{
    public: 
        App(int windowWidth, int windowHeight, int gridWidth, int gridHeight);
        ~App();

        void run();
    private:
        GLFWwindow* m_window = nullptr;
        int m_windowWidth;
        int m_windowHeight;

        Grid m_grid;
        std::unique_ptr<Renderer> m_renderer;   // ahora puntero
        bool m_leftMouseDown = false;

        // NUEVO:
        int m_lastCellX = -1;
        int m_lastCellY = -1;

        void processInput();
        void handleMouse();
    };