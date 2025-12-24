#include "App.hpp"

int main(){
    int windowWidth = 800;
    int windowHeight = 600;
    int gridWidth = 20;
    int gridHeight = 20;

    App app(windowWidth, windowHeight, gridWidth, gridHeight);
    app.run();

    return 0;
}