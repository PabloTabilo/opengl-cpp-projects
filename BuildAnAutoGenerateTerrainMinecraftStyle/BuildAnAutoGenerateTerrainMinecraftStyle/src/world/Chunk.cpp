#include "Chunk.h"

const float gap = 1.1f;
Chunk::Chunk() {
	float newXpos = 0.0f;
	float gap = 1.1f;
	float prevPos = 2.0f;
	float newPos;
	for (unsigned int x = 0; x < SIZE; x++) {
		for (unsigned int y = 0; y < SIZE; y++) {
			for(unsigned int z = 0; z < SIZE; z++)
			cubes.push_back(new Block(glm::vec3((x*1.0f), (y*1.0f), (z*1.0f) ) ) );
		}
	}

}