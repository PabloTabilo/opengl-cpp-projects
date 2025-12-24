
#pragma once
#include<glm/glm.hpp>

struct Bullet{
    Bullet(const glm::vec2& startPos, const glm::vec2& velocity);
    void update(float dt);
    const glm::vec2& getPosition() const { return pos; }
    bool isAlive() const { return alive; }
    void kill() { alive = false; }
    glm::vec2 pos;
    glm::vec2 vel;
    bool alive = true;
};