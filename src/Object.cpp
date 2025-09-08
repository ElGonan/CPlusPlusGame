#include "Object.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Object::Object(float startX, float startY, float width, float height, const std::string &spritePath, sf::Color color) :
    Obstacle(startX, startY, width, height, color),
    m_texture(),  // Initialize textures
    m_sprite(m_texture)  // Initialize sprite with texture
{
    // Load texture from file
    if (!m_texture.loadFromFile(spritePath)) {
        std::cerr << "Error: No se pudo cargar la textura potion.png" << std::endl;
    }
    
    //  Update sprite with texture
    m_sprite.setTexture(m_texture, true); // Reset rect to texture size
    m_sprite.setPosition(sf::Vector2f(startX, startY));
    m_sprite.setScale(sf::Vector2f(width / m_texture.getSize().x, height / m_texture.getSize().y));
    m_visible = true;

}

// Override getBounds to return sprite bounds if visible
sf::FloatRect Object::getBounds() const {
    if (m_visible) {
        return m_sprite.getGlobalBounds();
    }
    return sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f)); // Return empty rect if not visible
}


// Override draw to only draw if visible
void Object::onContact() {
    if (m_visible) {
        disappear();
    }

}

// Render sprite if visible
void Object::draw(sf::RenderWindow &window) {
    if (m_visible)
        window.draw(m_sprite);

        // draw hitbox, debug only
        // sf::FloatRect bounds = m_sprite.getGlobalBounds();
        // sf::RectangleShape hitbox;
        // hitbox.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
        // hitbox.setSize(sf::Vector2f(bounds.size.x, bounds.size.y));
        // hitbox.setFillColor(sf::Color::Transparent);
        // hitbox.setOutlineColor(sf::Color::Red);
        // hitbox.setOutlineThickness(1.0f);
        // window.draw(hitbox);

}

// Make the object disappear
void Object::disappear() {
    m_visible = false;
}

// Check if the object is visible
bool Object::isVisible() {
    return m_visible;
}