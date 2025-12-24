#include "Renderer.hpp"
#include "Shader.hpp"

#include <glad/glad.h>

Renderer::Renderer(int gridWidth, int gridHeight)
    : m_gridWidth(gridWidth), m_gridHeight(gridHeight)
{
    initQuad();
    initTexture();
    initShaders();
}

Renderer::~Renderer()
{
    glDeleteTextures(1, &m_texture);
    glDeleteBuffers(1, &m_vbo);
    //glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
    glDeleteProgram(m_program);
}

void Renderer::initQuad() {
    float vertices[] = {
        // pos      // tex
        -1.f, -1.f, 0.f, 0.f, // bottom-left
         1.f, -1.f, 1.f, 0.f, // bottom-right
        -1.f,  1.f, 0.f, 1.f, // top-left
         1.f,  1.f, 1.f, 1.f  // top-right
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout (location = 0) -> vec2 position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // layout (location = 1) -> vec2 texcoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // no usamos EBO, no indices
}


void Renderer::initTexture(){
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_gridWidth, m_gridHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // tiles enteros se ven bien
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::initShaders(){
    m_program = createShaderProgram("shaders/grid.vert", "shaders/grid.frag");
}

void Renderer::resize(int windowWidth, int windowHeight){
    glViewport(0, 0, windowWidth, windowHeight);
}

void Renderer::render(const std::vector<uint8_t>& colorBuffer){
    glUseProgram(m_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Actualizar textura
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_gridWidth, m_gridHeight, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer.data());

    int loc = glGetUniformLocation(m_program, "uGridTex");
    glUniform1i(loc, 0);
    
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  // <--- 4 vértices, 2 triángulos
    glBindVertexArray(0);
}