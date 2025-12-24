#pragma once
#include <vector>
#include <cstdint>

class Renderer{
    public:
        Renderer(int gridWidth, int gridHeight);
        ~Renderer();

        void resize(int windonWidth, int windowHeight);
        void render(const std::vector<uint8_t>& colorBuffer);
    private:
        unsigned int m_vao;
        unsigned int m_vbo;
        unsigned int m_ebo;
        unsigned int m_program;
        unsigned int m_texture;

        int m_gridWidth;
        int m_gridHeight;

        void initQuad();
        void initTexture();
        void initShaders();
};