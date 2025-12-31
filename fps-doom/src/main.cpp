// main.cpp
#include "App.hpp"
#include<iostream>

int windowWidth = 1280;
int windowHeight = 720;

int main() {
    try{
	App app(windowWidth, windowHeight);
	app.run();
    } catch(const std::exception& e){
	std::cerr << "Error: " << e.what() << std::endl;
	return -1;
    }
    return 0;
} 
