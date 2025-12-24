#pragma once
#include<glm/glm.hpp>
#include<vector>
#include <cstdlib>
#include<iostream>
#include"Bullet.hpp"

struct Enemy{
    Enemy(const glm::vec2& startPos,
          float fallSpeed,
          float shootIntervalMin,
          float shootIntervalMax
    );
    void update(float dt, std::vector<Bullet>& bulletsOut);

    void respawn(float x, float y){
        pos.x = x;
        pos.y = y;
        shootTimer = randomInterval();
    }

    glm::vec2 pos;
    float speed;
    float shootTimer; // tiempo para prox disparo
    float shootIntervalMin;
    float shootIntervalMax;

    float randomInterval() const;
};