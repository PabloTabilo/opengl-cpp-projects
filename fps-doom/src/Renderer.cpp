// Renderer.cpp
#include "Renderer.hpp"
#include <cstdlib>
#include <vector>
#include <functional>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

Renderer::Renderer(int width, int height) 
: width(width), height(height), 
    shader("shaders/basic.vert", "shaders/basic.frag"),
    tex("resources/textures/wall.jpg")
{
    //initQuad();
    initCube();

    generateMaze();
}

void Renderer::initQuad(){
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

void Renderer::initCube(){
    float vertices[] = {
	// position           // normal            // tex
	-0.5f,-0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   0.0f,0.0f,
	 0.5f,-0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   1.0f,0.0f,
	 0.5f, 0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   1.0f,1.0f,
	 0.5f, 0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   1.0f,1.0f,
	-0.5f, 0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   0.0f,1.0f,
	-0.5f,-0.5f,-0.5f,  0.0f, 0.0f,-1.0f,   0.0f,0.0f,

	-0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   0.0f,0.0f,
	 0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   1.0f,0.0f,
	 0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   1.0f,1.0f,
	 0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   1.0f,1.0f,
	-0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   0.0f,1.0f,
	-0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f,   0.0f,0.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   1.0f,0.0f,
	-0.5f, 0.5f,-0.5f, -1.0f, 0.0f, 0.0f,   1.0f,1.0f,
	-0.5f,-0.5f,-0.5f, -1.0f, 0.0f, 0.0f,   0.0f,1.0f,
	-0.5f,-0.5f,-0.5f, -1.0f, 0.0f, 0.0f,   0.0f,1.0f,
	-0.5f,-0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   0.0f,0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,   1.0f,0.0f,

	 0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,   1.0f,0.0f,
	 0.5f, 0.5f,-0.5f,  1.0f, 0.0f, 0.0f,   1.0f,1.0f,
	 0.5f,-0.5f,-0.5f,  1.0f, 0.0f, 0.0f,   0.0f,1.0f,
	 0.5f,-0.5f,-0.5f,  1.0f, 0.0f, 0.0f,   0.0f,1.0f,
	 0.5f,-0.5f, 0.5f,  1.0f, 0.0f, 0.0f,   0.0f,0.0f,
	 0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f,   1.0f,0.0f,

	-0.5f,-0.5f,-0.5f,  0.0f,-1.0f, 0.0f,   0.0f,1.0f,
	 0.5f,-0.5f,-0.5f,  0.0f,-1.0f, 0.0f,   1.0f,1.0f,
	 0.5f,-0.5f, 0.5f,  0.0f,-1.0f, 0.0f,   1.0f,0.0f,
	 0.5f,-0.5f, 0.5f,  0.0f,-1.0f, 0.0f,   1.0f,0.0f,
	-0.5f,-0.5f, 0.5f,  0.0f,-1.0f, 0.0f,   0.0f,0.0f,
	-0.5f,-0.5f,-0.5f,  0.0f,-1.0f, 0.0f,   0.0f,1.0f,

	-0.5f, 0.5f,-0.5f,  0.0f, 1.0f, 0.0f,   0.0f,1.0f,
	 0.5f, 0.5f,-0.5f,  0.0f, 1.0f, 0.0f,   1.0f,1.0f,
	 0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,   1.0f,0.0f,
	 0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,   1.0f,0.0f,
	-0.5f, 0.5f, 0.5f,  0.0f, 1.0f, 0.0f,   0.0f,0.0f,
	-0.5f, 0.5f,-0.5f,  0.0f, 1.0f, 0.0f,   0.0f,1.0f
    };
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // pos
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // light
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // tex
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

}

void Renderer::drawCube(const glm::mat4& model){
    glUniformMatrix4fv(
	    shader.getUniformLocation("model"), 
	    1, 
	    GL_FALSE, 
	    glm::value_ptr(model)
	);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.id());
    glUniform1i(shader.getUniformLocation("texture1"), 0);

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void Renderer::renderScene(const Camera& camera){
    // clear buffers
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shader.use();
    
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.Zoom),
	    (float)width/(float)height, 0.1f, 100.0f);
    
    glUniformMatrix4fv(shader.getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(proj));
    
    // ---- luces globales ----

    glm::vec3 lightPos(0.0f, 5.0f, 0.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

    glUniform3fv(shader.getUniformLocation("lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(shader.getUniformLocation("lightColor"), 1, glm::value_ptr(lightColor));
    glUniform3fv(shader.getUniformLocation("viewPos"), 1, glm::value_ptr(camera.Position));

    
    // base
    for(int x=-mx;x<=mx;x++){
	for(int z=-mx;z<=mx;z++){
	    glm::mat4 m(1.0f);
	    m = glm::translate(m, glm::vec3(x, 0.0f, z));
	    drawCube(m);
	}
    }
    // pared izq
    for(int z=-mx;z<=mx;z++){
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(-10.f, 1.0f, z));
	drawCube(m);
    }
    // pared derecha
    for(int z=-mx;z<=mx;z++){
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(10.f, 1.0f, z));
	drawCube(m);
    }
    // pared fondo
    for(int x=-mx;x<=mx;x++){
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(x, 1.0f, -10.0f));
	drawCube(m);
    }
    
    for(int x=0;x<M;x++){
	for(int z=0;z<M;z++){
	    if(positions[x][z]){
		int rx = x - N;
		int rz = z - N;
		glm::mat4 m(1.0f);
		m = glm::translate(m, glm::vec3(rx, 1.0f, rz));
		drawCube(m);
	    }
	}
    }

    /*
    // laberinto simple
    for(int i=-5;i<=5;i++){
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(i, 1.0f, 2.0f));
	drawCube(m);
    }
    for(int i=2;i<=6;i++){
	glm::mat4 m(1.0f);
	m = glm::translate(m, glm::vec3(5.0f, 1.0f, i));
	drawCube(m);
    }
    */
}

void Renderer::renderScene2(const Camera& camera){
    // clear buffers
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    glm::mat4 view = camera.GetViewMatrix();
    float aspect = (float)width / (float)height;
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), aspect, 0.1f, 100.0f);

    GLint locView = shader.getUniformLocation("view");
    GLint locProj = shader.getUniformLocation("projection");
    glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 1.0f, -3.0f));
    GLint locModel = shader.getUniformLocation("model");
    glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.id());
    glUniform1i(shader.getUniformLocation("texture1"), 0);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void Renderer::generateMaze(){
    this->mx = 50;
    this->N = mx-1;
    int moves[4][2] = {
	{1,0},{-1,0},{0,1},{-1,0}
    };
    this->M = 2*N;
    positions.assign(M, std::vector<bool>(M, false));

    std::function<void(int, int, int)> dfs;
    dfs = [&](int x, int z, int ite){
	if(ite <= 0) return;
	int gen = 1;
	int nx = x;
	int nz = z;
	while(gen < 20){
	    int nxt = rand() % 4;
	    int addX = moves[nxt][0];
	    int addZ = moves[nxt][1];
	    nx = x + addX;
	    nz = z + addZ;
	    if(nx >= 0 && nz >= 0 && nx < M && nz < M) break;
	    gen++;
	}
	if(gen >= 20) return;
	positions[nx][nz] = true;
	dfs(nx, nz, ite-1);
    };
    for(int ite = 0; ite < 70; ite++){
	int x, z;
	x = rand() % (2*N);
	z = rand() % (2*N);
	positions[x][z] = true;
	dfs(x, z, N-1);
    }
    
    cout << "random positions using dfs: " << endl;
    for(auto r : positions){
	for(auto c : r){
	    cout << c << " ";
	}
	cout << endl;
    }
    cout << endl;
    

}


