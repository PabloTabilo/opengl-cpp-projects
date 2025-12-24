// Renderer.cpp
#include "Renderer.hpp"

Renderer::Renderer(int width, int height) 
: width(width), height(height), 
    shader("shaders/basic.vert", "shaders/basic.frag"),
    tex("resources/textures/wall.jpg")
{
	float vertices[] = {
	     0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	    -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
	    0, 1, 3,
	    1, 2, 3
	};
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	// position attribute	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
}

Renderer::~Renderer(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::clear(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::onResize(int newWidth, int newHeight){
    width = newWidth;
    height = newHeight;
}

void Renderer::drawTriangle(
	const glm::vec2& pos,
	const glm::vec2& scale,
	const glm::vec3& color
	){
    shader.use();

    glm::mat4 transform(1.f);
    transform = glm::translate(transform, glm::vec3(pos, 0.f));
    transform = glm::scale(transform, glm::vec3(scale, 1.f));

    GLint locTransform = shader.getUniformLocation("transform");
    glUniformMatrix4fv(locTransform, 1, GL_FALSE, glm::value_ptr(transform));

    GLint locColor = shader.getUniformLocation("uColor");
    glUniform3fv(locColor, 1, glm::value_ptr(color));

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void Renderer::drawSquare(const glm::vec2& pos)
{
    shader.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex.id());
	glUniform1i(shader.getUniformLocation("texture1"), 0);
    glm::mat4 transform(1.f);
    transform = glm::translate(transform, glm::vec3(pos, 0.f));
    GLint locTransform = shader.getUniformLocation("transform");
    glUniformMatrix4fv(locTransform, 1, GL_FALSE, glm::value_ptr(transform));

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


