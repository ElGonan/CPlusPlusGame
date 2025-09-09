#include "Stickman.h"
#include "globals.h"
#include "Obstacle.h"
#include "Object.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <cmath>

Stickman::Stickman(float startX, float startY) :
    m_speed(STICKMAN_SPEED),
    m_IsJumping(false),
    m_jumpHeight(STICKMAN_JUMP_HEIGHT),
    m_color(STICKMAN_COLOR),

    m_isPushed(false),
    m_pushForce(300.0f),
    m_pushDuration(0.2f),
    m_pushTimer(0.0f),
    m_HP(100.0f),
    m_maxHP(100.0f)

{
    m_shape.setSize(sf::Vector2f(STICKMAN_SIZE, STICKMAN_SIZE));
    m_shape.setPosition(sf::Vector2f(startX, startY));
    m_shape.setFillColor(m_color);
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !m_IsJumping) {
        m_velocity.y = -m_jumpHeight;
        m_IsJumping = true;
    }
}

void Stickman::checkCollision(const Obstacle& obstacle) {
    sf::FloatRect stickmanBounds = m_shape.getGlobalBounds();
    sf::FloatRect obstacleBounds = obstacle.getBounds();

    auto intersection = stickmanBounds.findIntersection(obstacleBounds);
    if (intersection != std::nullopt) {

        Object* obj = dynamic_cast<Object*>(const_cast<Obstacle*>(&obstacle));
        if (obj) {
            obj->onContact();
        }
        
        float intersectWidth = intersection->size.x;
        float intersectHeight = intersection->size.y;

        // Decide si la colisión es lateral o vertical
        if (intersectWidth < intersectHeight) {
            // Colisión lateral
            if (stickmanBounds.position.x < obstacleBounds.position.x) {
                // Colisión desde la izquierda
                m_shape.setPosition(sf::Vector2f(obstacleBounds.position.x - stickmanBounds.size.x, m_shape.getPosition().y));
            } else {
                // Colisión desde la derecha
                m_shape.setPosition(sf::Vector2f(obstacleBounds.position.x + obstacleBounds.size.x, m_shape.getPosition().y));
            }
            m_velocity.x = 0.0f;
        } else {
            // Colisión vertical
            if (stickmanBounds.position.y < obstacleBounds.position.y) {
                // Colisión desde arriba
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, obstacleBounds.position.y - stickmanBounds.size.y));
                m_velocity.y = 0.0f;
                m_IsJumping = false;
            } else {
                // Colisión desde abajo
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, obstacleBounds.position.y + obstacleBounds.size.y));
                m_velocity.y = 0.0f;
                m_IsJumping = true;
            }
        }
    }
}

void Stickman::checkCollision(const Stickman& other) {
    sf::FloatRect stickmanBounds = m_shape.getGlobalBounds();
    sf::FloatRect otherBounds = other.getBounds();

    auto intersection = stickmanBounds.findIntersection(otherBounds);
    if (intersection != std::nullopt) {
        // Calcular dirección del retroceso
        sf::Vector2f direction(
            m_shape.getPosition().x - other.getPosition().x,
            m_shape.getPosition().y - other.getPosition().y
        );
        
        // Normalizar la dirección
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }
        
        // Aplicar retroceso
        pushBack(direction);
        
        // Ajustar posición para evitar solapamiento
        float intersectWidth = intersection->size.x;
        float intersectHeight = intersection->size.y;

        if (intersectWidth < intersectHeight) {
            if (stickmanBounds.position.x < otherBounds.position.x) {
                m_shape.setPosition(sf::Vector2f(otherBounds.position.x - stickmanBounds.size.x, m_shape.getPosition().y));
            } else {
                m_shape.setPosition(sf::Vector2f(otherBounds.position.x + otherBounds.size.x, m_shape.getPosition().y));
            }
        } else {
            if (stickmanBounds.position.y < otherBounds.position.y) {
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, otherBounds.position.y - stickmanBounds.size.y));
                m_velocity.y = 0.0f;
                m_IsJumping = false;
            } else {
                m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, otherBounds.position.y + otherBounds.size.y));
                m_velocity.y = 0.0f;
                m_IsJumping = true;
            }
        }
    }
}

void Stickman::update(float deltaTime, const std::vector<Obstacle*>& obstacles) {
    updatePush(deltaTime);

    if (!m_isPushed)
    {
        m_velocity.y += GRAVITY * deltaTime;
    }

    
    // Move the Stickman
    m_shape.move(m_velocity * deltaTime);

    // Check for collisions with all obstacles
    for (Obstacle* obstacle : obstacles) {
        checkCollision(*obstacle);
    }

    if (!m_isPushed)
    {
       handleInput();
    }
    
    
    
}

void Stickman::update(float deltaTime,const std::vector<Obstacle*>& obstacles , const std::vector<Stickman*>& enemies) {
    update(deltaTime, obstacles);
    // Check for collisions with other stickmen
    for (const auto& other : enemies) {
        if (other != this) { // Avoid self-collision
            checkCollision(*other);
        }
    }
}

void Stickman::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

sf::FloatRect Stickman::getBounds() const {
    return m_shape.getGlobalBounds();
}

void Stickman::pushBack(const sf::Vector2f& direction) {
    if (!m_isPushed) {
        m_velocity = direction * m_pushForce;
        m_isPushed = true;
        m_pushTimer = 0.0f;
    }
}

void Stickman::updatePush(float deltaTime) {
    if (m_isPushed) {
        m_pushTimer += deltaTime;
        if (m_pushTimer >= m_pushDuration) {
            m_isPushed = false;
            m_velocity.x = 0.0f; // Detener el retroceso después de la duración
        }
    }
}
