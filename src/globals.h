#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/Graphics.hpp>
#include <string>


// routes
extern std::string fontPath;
extern std::string spritePath;
extern std::string backgroundPath;

// Screen dimensions
extern const float S_W;
extern const float S_H;

// Background color
extern int R_BG;
extern int G_BG;
extern int B_BG;

extern float GRAVITY; // pixels per second squared

// Stickman size and values
extern sf::Color STICKMAN_COLOR;
extern float STICKMAN_HEIGHT;
extern const float STICKMAN_WIDTH;
extern float STICKMAN_SPEED;
extern float STICKMAN_JUMP_HEIGHT;
extern float STICKMAN_SIZE;
// Camera settings
extern float CAMERA_SMOOTHING;
extern float CAMERA_INITIAL_POS_X;
extern float CAMERA_INITIAL_POS_Y;

#endif // GLOBALS_H