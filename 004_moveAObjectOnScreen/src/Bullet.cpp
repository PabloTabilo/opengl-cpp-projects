#include "Bullet.hpp"

Bullet::Bullet(const glm::vec2& startPos, const glm::vec2& velocity)
    : pos(startPos), vel(velocity), alive(true) {}

void Bullet::update(float dt) {
    if(!alive) return;
    pos += vel * dt;
    if(pos.y < -1.2f || pos.y > 1.2f){
        alive = false;
    }
}