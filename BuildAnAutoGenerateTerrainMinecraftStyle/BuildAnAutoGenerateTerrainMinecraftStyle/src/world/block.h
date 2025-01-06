#ifndef BLOCK_H
#define BLOCK_H

#include<glm/glm.hpp>

class Block {
public:
	static const float vertices[];
	static constexpr size_t verticesSize = 180;
	Block(glm::vec3 position);
	glm::vec3 getPosition();
	void setHeight(float y);
private:
	glm::vec3 position;
};

#endif