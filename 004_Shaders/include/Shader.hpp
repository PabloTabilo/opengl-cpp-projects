#pragma once

#include <glad/glad.h>
#include <string>

class Shader{
    public:
	Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
	~Shader();
	void use() const;
	GLuint id() const {return program;}
	GLint getUniformLocation(const std::string& name) const;
    private:
	GLuint program;
	static std::string loadFile(const std::string& filepath);
	static GLuint compileShader(GLenum type, const std::string& source);
};
