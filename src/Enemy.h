#ifndef ENEMY_H
#define ENEMY_H

#include "Stickman.h"

class Enemy : public Stickman {
public:
    Enemy(float startX, float startY);
    void handleInput() override; // Sobrescribe el manejo de entrada
    void update(float deltaTime) override; // Sobrescribe la actualización
    
};

#endif // ENEMY_H