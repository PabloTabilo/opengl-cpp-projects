#include "Enemy.hpp"

Enemy::Enemy(const glm::vec2& startPos,
               float fallSpeed,
               float shootIntervalMin,
               float shootIntervalMax
)
    : pos(startPos),
      speed(fallSpeed),
      shootIntervalMin(shootIntervalMin),
      shootIntervalMax(shootIntervalMax)
{
    shootTimer = randomInterval();
}

float Enemy::randomInterval() const {
    float t = static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    return shootIntervalMin + t * (shootIntervalMax - shootIntervalMin);
}

void Enemy::update(float dt, std::vector<Bullet>& bulletsOut) {
    // Mover hacia abajo
    pos.y -= speed * dt;

    if(pos.y < -1.1f){
        pos.y = 0.9f;
    }
    //std::cout << "Enemy position: (" << pos.x << ", " << pos.y << ")\n";
    shootTimer -= dt;
    
    if (shootTimer <= 0.0f) {
        // Disparar un proyectil hacia abajo
        //std::cout << "Enemy shootTimer: " << shootTimer << "\n";
        //std::cout << "Enemy fired at y=" << pos.y << "\n";
        Bullet b(pos, glm::vec2(0.0f, -0.8f));
        bulletsOut.emplace_back(b);

        // Reiniciar el temporizador de disparo
        shootTimer = randomInterval();
    }
}