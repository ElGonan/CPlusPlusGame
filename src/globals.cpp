#include "globals.h"
#include <SFML/Graphics.hpp>


// My god, THESE PATHS ARE FOR WINDOWS, uncomment and comment the others if you're on Windows
// std::string fontPath = "../assets/fonts/minecraft_font.ttf";
// std::string spritePath = "../assets/sprite/potion.png";
// std::string backgroundPath = "../assets/background/elation.png";

// Linux & macOS paths
std::string fontPath = "assets/fonts/minecraft_font.ttf";
std::string spritePath = "assets/sprite/potion.png";
std::string backgroundPath = "assets/background/elation.png";


const float S_H = 800.0f;
const float S_W = 1000.0f;

int R_BG = 255;
int G_BG = 255;
int B_BG = 255;

float GRAVITY = 981.0; // pixels per second squared

// Stickman settings
sf::Color STICKMAN_COLOR = sf::Color::Red;
float STICKMAN_HEIGHT = 500.0f;
const float STICKMAN_WIDTH = 250.0f;
float STICKMAN_SPEED = 500.0f;
float STICKMAN_JUMP_HEIGHT = 750.0f;
float STICKMAN_SIZE = 50.0f;

// Camera settings
float CAMERA_SMOOTHING = 1.0f;
float CAMERA_INITIAL_POS_X = S_W / 2.0f;
float CAMERA_INITIAL_POS_Y = S_H / 2.0f;