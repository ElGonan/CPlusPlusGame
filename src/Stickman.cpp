#include "Stickman.h"
#include "globals.h"
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

    // collision con paredes
    if(m_shape.getPosition().x < 0.0f || m_shape.getPosition().x + m_shape.getSize().x > S_W) {
        m_velocity.x = 0.0f;
        if(m_shape.getPosition().x < 0.0f) {
            m_shape.setPosition(sf::Vector2f(0.0f, m_shape.getPosition().y));
        } else {
            m_shape.setPosition(sf::Vector2f(S_W - m_shape.getSize().x, m_shape.getPosition().y));
        }
    }
}

void Stickman::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

sf::FloatRect Stickman::getBounds() {
    return m_shape.getGlobalBounds();
}