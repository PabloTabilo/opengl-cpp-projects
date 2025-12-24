#include "App.hpp"
#include <iostream>
#include <algorithm>

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if(app){
        app->onResize(width, height);
    }
    glViewport(0, 0, width, height);
}

App::App(int width, int height) : width(width), height(height){
    
    std::random_device rd;
    rng = std::mt19937(rd());

    if(!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(width, height, "OpenGL App", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    renderer = std::make_unique<Renderer>(width, height);
    initEnemies();
}

App::~App() {
    // Destructor implementation
    if(window){
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

void App::run() {
    double lastTime = glfwGetTime();
    // Main loop implementation
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    while(!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        processInput(deltaTime);
        update(deltaTime);
        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void App::onResize(int newWidth, int newHeight) {
    width = newWidth;
    height = newHeight;
    renderer->onResize(newWidth, newHeight);
}

void App::initEnemies() {
    enemies.clear();
    int N = 8;
    float y = 1.0f;

    float baseSpeed = 0.2f;
    float shootMinSeconds = 1.0f;
    float shootMaxSeconds = 2.5f;

    for(int i = 0; i < N; ++i) {
        float x = enemySpawnX(rng);
        glm::vec2 pos(x, y);
        float speed = baseSpeed + static_cast<float>(i) * 0.05f;
        enemies.emplace_back(
            pos,
            speed,
            shootMinSeconds,
            shootMaxSeconds
        );
    }
}

void App::processInput(float deltaTime) {
    float step = playerSpeed * deltaTime;
    // Input processing implementation
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // Additional input handling can be added here
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        playerPos.y += step;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        playerPos.y -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        playerPos.x -= step;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        playerPos.x += step;
    }

    if(playerFireCooldown > 0.0f) {
        playerFireCooldown -= deltaTime;
        if(playerFireCooldown < 0.0f) {
            playerFireCooldown = 0.0f;
        }
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && playerFireCooldown <= 0.0f) {
        // Shoot bullet
        playerBullets.emplace_back(
            playerPos,
            glm::vec2(0.0f, 1.0f) * 1.0f // bullet speed
        );
        playerFireCooldown = playerFireInterval;
    }
}

void App::update(float dt){
    updateEnemies(dt);
    updateBullets(dt, enemyBullets);
    updateBullets(dt, playerBullets);
    handleCollisions();
}

void App::updateEnemies(float dt) {
    for(auto& enemy : enemies) {
        enemy.update(dt, enemyBullets);
        if(enemy.pos.y < -1.1f) {
            float x = enemySpawnX(rng);
            enemy.pos = glm::vec2(x, 1.0f);
        }
    }
}

void App::updateBullets(float dt, std::vector<Bullet>& v) {
    for(auto& bullet : v) {
        bullet.update(dt);
    }
    v.erase(
        std::remove_if(v.begin(), v.end(),
                       [](const Bullet& b){ return !b.isAlive(); }),
        v.end()
    );
}

void App::handleCollisions() {
    // Collision handling implementation
    // Check collisions between player bullets and enemies

    for(auto& enemy : enemies) {
        for(auto& bullet : playerBullets) {
            if(!bullet.isAlive()) continue;

            if(checkCollision(bullet.getPosition(), bulletHalfSize,
                              enemy.pos, enemyHalfSize)) {
                bullet.kill();
                float x = enemySpawnX(rng);
                enemy.respawn(x, 1.0f);
            }
        }
    }

    // Check collisions between enemy bullets and player
    for(auto& bullet : enemyBullets) {
        if(!bullet.isAlive()) continue;
        if(checkCollision(bullet.getPosition(), bulletHalfSize,
                          playerPos, playerHalfSize)) {
            bullet.kill();
            // Handle player hit (e.g., reduce health or end game)
            std::cout << "Player hit!\n";
            playerPos = glm::vec2(0.0f, -0.8f); // Reset player position
        }
    }
}

bool App::checkCollision(const glm::vec2& p1, const glm::vec2& half1,
                         const glm::vec2& p2, const glm::vec2& half2) {
    bool overlapX = std::abs(p1.x - p2.x) <= (half1.x + half2.x);
    bool overlapY = std::abs(p1.y - p2.y) <= (half1.y + half2.y);

    return overlapX && overlapY;
}

void App::render() {
    //std::cout << "enemyBullets size = " << enemyBullets.size() << "\n";
    renderer->clear();
    renderer->drawTriangle(
        playerPos,
        glm::vec2(1.0f, 1.0f),
        glm::vec3(1.f, 0.f, 0.f)
    );
    for(const auto& enemy : enemies) {
        renderer->drawTriangle(
            enemy.pos,
            glm::vec2(1.f, 1.f),
            glm::vec3(0.0f, 1.f, 0.f)
        );
    }
    for(const auto& bullet : enemyBullets) {
        //std::cout << "Bullet position: (" << bullet.getPosition().x << ", " << bullet.getPosition().y << ")\n";
        renderer->drawTriangle(
            bullet.getPosition(),
            glm::vec2(0.4f, 0.6f),
            glm::vec3(0.f, 0.f, 1.0f)
        );
    }
    for(const auto& bullet : playerBullets) {
        //std::cout << "Bullet position: (" << bullet.getPosition().x << ", " << bullet.getPosition().y << ")\n";
        renderer->drawTriangle(
            bullet.getPosition(),
            glm::vec2(0.4f, 0.6f),
            glm::vec3(0.f, 1.f, 1.0f)
        );
    }
}
