#include "Enemy.h"

Enemy::Enemy(float startX, float startY) : Stickman(startX, startY) {
    // Puedes inicializar propiedades específicas de Enemy aquí
    m_shape.setFillColor(sf::Color::Blue); // Ejemplo: cambiar color
}

void Enemy::handleInput() {
    // Implementación específica para Enemy (vacía o con lógica de IA)
    m_velocity.x = 0.0f;
    
    // Ejemplo de movimiento automático simple (opcional)
    static bool movingRight = true;
    if (movingRight) {
        m_velocity.x = m_speed;
    } else {
        m_velocity.x = -m_speed;
    }
    
    // Lógica para cambiar dirección (ejemplo)
    if (m_shape.getPosition().x > S_W - m_shape.getSize().x) {
        movingRight = false;
    } else if (m_shape.getPosition().x < 0) {
        movingRight = true;
    }
}