#include "block.h";

const float Block::vertices[] = {
	// positions          // texCoords
	// Back face
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left
	0.5f, -0.5f, -0.5f,  0.25f, 0.0f, // bottom-right
	0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
	0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
   -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // bottom-left

   // Front face
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
   0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
   0.5f,  0.5f,  0.5f,  0.25f, 1.0f, // top-right
   0.5f,  0.5f,  0.5f,  0.25f, 1.0f, // top-right
  -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // top-left
  -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left

  // Left face
 -0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-right
 -0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-left
 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-left
 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-left
 -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-right
 -0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-right

 // Right face
 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-left
 0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-right
 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // bottom-right
 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // top-left

 // Bottom face
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // top-left
 0.5f, -0.5f, -0.5f,  0.25f, 1.0f, // top-right
 0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
 0.5f, -0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  // top-left

// Top face
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // top-left
 0.5f,  0.5f, -0.5f,  0.25f, 1.0f, // top-right
 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
 0.5f,  0.5f,  0.5f,  0.25f, 0.0f, // bottom-right
-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  // bottom-left
-0.5f,  0.5f, -0.5f,  0.0f, 1.0f   // top-left
};

Block::Block(glm::vec3 pos) {
	position = pos;
}

glm::vec3 Block::getPosition() {
	return position;
}

void Block::setHeight(float y) {
	position[1] = y;
}


