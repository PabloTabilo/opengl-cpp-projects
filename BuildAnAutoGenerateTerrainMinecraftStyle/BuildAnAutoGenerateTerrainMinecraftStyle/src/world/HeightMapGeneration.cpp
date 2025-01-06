#include "HeightMapGeneration.h"

float HeightMapGeneration::randomImportance = 0.1f;

HeightMapGeneration::HeightMapGeneration(int size) {
	this->size = size;
	this->step = size-1;
	myMap.resize(size, std::vector<float>(size, 0.0f));
	mapToindx.resize(size * size, 0.0f);

	for (uint32_t y = 0; y < size; y += step) {
		for (uint32_t x = 0; x < size; x += step) {
			myMap[y][x] = randomFloatUniform();
			mapToindx[coordsToIndex(y, x)] = myMap[y][x];
		}
	}

	build();

}

uint32_t HeightMapGeneration::coordsToIndex(uint32_t y, uint32_t x) {
	return y * uint32_t(size) + x;
}

void HeightMapGeneration::build() {

	while (step > 1) {
		half = step / 2;

		diamondAlgorithm();
		squareAlgorithm();

		randomImportance /= 2.f;
		step /= 2;
	}
}

void HeightMapGeneration::diamondAlgorithm() {
	for (uint32_t y = half; y < size; y += step) {
		for (uint32_t x = half; x < size; x += step) {
			float val = 0.0f;
			int cnt = 0;
			if ((y - half) >= 0 && (x - half) >= 0) {
				val += myMap[y - half][x - half];
				cnt++;
			}
			if ((y - half) >= 0 && (x + half) < size) {
				val += myMap[y - half][x + half];
				cnt++;
			}
			if ((y + half) < size && (x - half) >= 0) {
				val += myMap[y + half][x - half];
				cnt++;
			}
			if ((y + half) < size && (x + half) < size) {
				val += myMap[y + half][x + half];
				cnt++;
			}
			myMap[y][x] = (val / float(cnt)) + (randomFloatUniform() * randomImportance);
			mapToindx[coordsToIndex(y, x)] = myMap[y][x];
		}
	}
}

void HeightMapGeneration::squareAlgorithm() {
	for (uint32_t y = 0; y < size; y += half) {
		for (uint32_t x = (y + half) % step; x < size; x += step) {
			float val = 0.0f;
			int cnt = 0;

			if (x >= half && (x - half) >= 0) {
				val += myMap[y][x - half];
				cnt++;
			}

			if ((x + half) < size) {
				val += myMap[y][x + half];
				cnt++;
			}

			if (y >= half && (y - half) >= 0) {
				val += myMap[y - half][x];
				cnt++;
			}

			if ((y + half) < size) {
				val += myMap[y + half][x];
				cnt++;
			}
			
			myMap[y][x] = (val / float(cnt)) + (randomFloatUniform() * randomImportance);
			mapToindx[coordsToIndex(y, x)] = myMap[y][x];
		}
	}
}



float HeightMapGeneration::randomFloatUniform() {
	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	return r;
}
