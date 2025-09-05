#include "Stickman.h"
#include "globals.h"
#include "Obstacle.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Stickman::Stickman(float startX, float startY) :
    m_speed(STICKMAN_SPEED),
    m_IsJumping(false),
    m_jumpHeight(STICKMAN_JUMP_HEIGHT)
{
    m_shape.setSize(sf::Vector2f(STICKMAN_SIZE, STICKMAN_SIZE));
    m_shape.setPosition(sf::Vector2f(startX, startY));
    m_shape.setFillColor(sf::Color::Red);
    m_velocity = sf::Vector2f(0.0f, 0.0f);
}

void Stickman::handleInput() {
    m_velocity.x = 0.0f;
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        m_velocity.x = -m_speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        m_velocity.x = m_speed;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !m_IsJumping) {
        m_velocity.y = -m_jumpHeight;
        m_IsJumping = true;
    }
}


void Stickman::checkCollision(const Stickman& other) {
    
    sf::FloatRect stickmanBounds = this->getBounds();
    sf::FloatRect otherBounce = other.getBounds();

    auto intersection = stickmanBounds.findIntersection(otherBounce);   

    if (intersection) {
              // Calcular superposición en cada eje
        float overlapLeft   = intersection->position.x + intersection->position.y  - otherBounce.position.x;
        float overlapRight  = otherBounce.position.x + otherBounce.position.x - intersection->position.x;
        float overlapTop    = intersection->position.y + intersection->position.y  - otherBounce.position.y;
        float overlapBottom = otherBounce.position.y + otherBounce.position.y - intersection->position.y;        
        // Encontrar la superposición mínima
        float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});
        
        if (minOverlap == overlapLeft) {
            // Colisión por la izquierda
            m_shape.setPosition(obstacleBounds.left - stickmanBounds.width, m_shape.getPosition().y);
            m_velocity.x = 0;
        } else if (minOverlap == overlapRight) {
            // Colisión por la derecha
            m_shape.setPosition(obstacleBounds.left + obstacleBounds.width, m_shape.getPosition().y);
            m_velocity.x = 0;
        } else if (minOverlap == overlapTop) {
            // Colisión por arriba (pisando el obstáculo)
            m_shape.setPosition(m_shape.getPosition().x, obstacleBounds.top - stickmanBounds.height);
            m_velocity.y = 0;
            m_IsJumping = false;
        } else if (minOverlap == overlapBottom) {
            // Colisión por abajo (golpeando cabeza)
            m_shape.setPosition(m_shape.getPosition().x, obstacleBounds.top + obstacleBounds.height);
            m_velocity.y = 0;
        }
    }
}


void Stickman::update(float deltaTime) {
    // Aplicar gravedad
    m_velocity.y += GRAVITY * deltaTime; // 981 píxeles/s²
    
    // Movimiento
    m_shape.move(m_velocity * deltaTime);
    
    // Colisión con el suelo
    if(m_shape.getPosition().y + m_shape.getSize().y > S_H) {
        m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, S_H - m_shape.getSize().y));
        m_velocity.y = 0.0f;
        m_IsJumping = false;
    }

    
    
}

void Stickman::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

sf::FloatRect Stickman::getBounds() const{
    return m_shape.getGlobalBounds();
}
