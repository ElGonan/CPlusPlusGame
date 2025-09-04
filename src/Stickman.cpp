#include "Stickman.h"
#include <iostream>

Stickman::Stickman(float startX, float startY) :
    m_speed(500.0f),
    m_IsJumping(false),
    m_jumpHeight(750.0f)
{
    m_shape.setSize(sf::Vector2f(50.0f, 50.0f));
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
    m_velocity.y += 981.0f * deltaTime; // 981 píxeles/s²
    
    // Movimiento
    m_shape.move(m_velocity * deltaTime);
    
    // Colisión con el "suelo" (simulado)



    // comment the todo if you want to test
    @TODO: add collision with walls


    if(m_shape.getPosition().y > 550.0f) {
        m_shape.setPosition(sf::Vector2f(m_shape.getPosition().x, 550.0f));
        m_velocity.y = 0.0f;
        m_IsJumping = false;
    }
}

void Stickman::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

sf::FloatRect Stickman::getBounds() {
    return m_shape.getGlobalBounds();
}