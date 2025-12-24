#include "App.hpp"
#include <iostream>

int main(){
    int windowWidth = 800;
    int windowHeight = 600;
    try{
        App app(windowWidth, windowHeight);
        app.run();
    } catch(const std::exception& e){
        // Handle initialization errors
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}