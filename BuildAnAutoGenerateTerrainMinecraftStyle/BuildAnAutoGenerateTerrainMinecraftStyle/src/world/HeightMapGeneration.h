#ifndef HEIGHTMAPGENERATION_H
#define HEIGHTMAPGENERATION_H

#include <random>
#include <vector>

struct HeightMapGeneration {
	static float randomImportance;
	std::vector<std::vector<float>> myMap;
	std::vector<float> mapToindx;
	int step;
	int size;
	int half;
	HeightMapGeneration(int size);
	uint32_t coordsToIndex(uint32_t y, uint32_t x);
	void diamondAlgorithm();
	void squareAlgorithm();
	void build();
	float randomFloatUniform();
};

#endif
