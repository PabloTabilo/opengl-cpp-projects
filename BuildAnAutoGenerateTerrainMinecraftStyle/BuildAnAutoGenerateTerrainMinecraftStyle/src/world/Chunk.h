#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "block.h"

struct Chunk {
	static const int SIZE = (1 << 5) + 1;
	static const float gap;
	std::vector<Block*> cubes;
	Chunk();
};


#endif