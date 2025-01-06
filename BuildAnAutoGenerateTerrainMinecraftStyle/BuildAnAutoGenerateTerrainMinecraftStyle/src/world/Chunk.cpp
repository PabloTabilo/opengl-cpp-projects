#include "Chunk.h";

const float gap = 1.1f;
Chunk::Chunk() {
	float newXpos = 0.0f;
	float gap = 1.1f;
	float prevPos = 2.0f;
	float newPos;
	for (unsigned int i = 0; i < SIZE; i++) {
		prevPos = 2.0f;
		for (unsigned int j = 0; j < SIZE; j++) {
			newPos = prevPos - gap;
			cubes.push_back(new Block(glm::vec3(newXpos, 0.0f, newPos)));
			prevPos = newPos;
		}
		newXpos += gap;
	}

}