#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <random>

#include <glm/glm.hpp>

#include "Renderer.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class App {
    public:
        App(int width, int height);
        ~App();
        void run();
        void onResize(int newWidth, int newHeight);
    private:
        GLFWwindow* window;
        int width;
        int height;

        std::mt19937 rng;
        std::uniform_real_distribution<float> enemySpawnX{-0.9f, 0.9f};

        std::unique_ptr<Renderer> renderer;

        // jugador
        glm::vec2 playerPos{0.0f, -0.8f};
        float playerSpeed = 1.f;

        // hitbox
        // collisions AABB half extents
        glm::vec2 playerHalfSize{0.06f, 0.06f};
        glm::vec2 enemyHalfSize{0.06f, 0.06f};
        glm::vec2 bulletHalfSize{0.02f, 0.04f};

        float playerFireCooldown = 0.0f;
        const float playerFireInterval = 0.1f;

        // enemigos y balas
        std::vector<Enemy> enemies;
        std::vector<Bullet> enemyBullets;
        std::vector<Bullet> playerBullets;

        void initEnemies();
        
        void processInput(float deltaTime);

        void update(float dt);
        void updateEnemies(float dt);
        void updateBullets(float dt, std::vector<Bullet>& v);

        void handleCollisions();
        bool checkCollision(const glm::vec2& p1, const glm::vec2& half1,
                            const glm::vec2& p2, const glm::vec2& half2);

        void render();
};