#include "Renderer.hpp"

Renderer::Renderer(int width, int height) : width(width), height(height), shader("shaders/basic.vert", "shaders/basic.frag"){
    float vertices[] = {
        // positions
         -0.05f,  -0.05f,
        0.05f, -0.05f,
         0.0f, 0.05f
    };
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Renderer::~Renderer() {
    // Destructor implementation
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Renderer::clear() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::onResize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
}
void Renderer::drawTriangle(
    const glm::vec2& pos,
    const glm::vec2& scale,
    const glm::vec3& color
) 
{
    shader.use();

    glm::mat4 transform(1.0f);
    transform = glm::translate(transform, glm::vec3(pos, 0.0f));
    transform = glm::scale(transform, glm::vec3(scale, 1.0f));

    GLint locTransform = shader.getUniformLocation("transform");
    glUniformMatrix4fv(locTransform, 1, GL_FALSE, glm::value_ptr(transform));

    GLint locColor = shader.getUniformLocation("uColor");
    glUniform3fv(locColor, 1, glm::value_ptr(color));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}