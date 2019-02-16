/*
	InvadersConstants.hpp - all numeric constants for Invaders Game - player size, speed, ...
*/

#ifndef constants_hpp_
#define constants_hpp_

#include "SFML/Graphics.hpp"

// Game configuration
static std::string CONFIG_PATH = "data/config/";

// Invaders
static constexpr int SCREEN_WIDTH = 1280; // width of game window
static constexpr int SCREEN_HEIGHT = 720; // height of game window

// player
static constexpr float PLAYER_START_POSITION_X = SCREEN_WIDTH / 2; // player starts at horizontal center of screen
static constexpr float PLAYER_START_POSITION_Y = SCREEN_HEIGHT; // player starts at down edge of screen
static constexpr float PLAYER_MIN_SHOOT_TIME = 0.2f; // time between two rockets shot by player
static constexpr float PLAYER_ENERGY_SHOOT = 0.15f; // how much energy is needed for each shot
extern float PLAYER_SPEED; // movement speed (pixels/s)
extern float PLAYER_ENERGY_RESTORE_RATE; // energy gained per second
extern int PLAYER_LIVES; // number of lives of player

// rockets
static constexpr float ROCKET_SIZE_X = 10.f; // size of rocket sprite
static constexpr float ROCKET_SIZE_Y = 45.f; // size of rocket sprite
static constexpr float ROCKET_SPEED = 700.f; // movements speed (pixels/s)

// explosions (animation)
static constexpr float EXPLOSION_SIZE = 80.f;  // size of player sprite
static constexpr float EXPLOSION_ANIMATION_SCALING_SPEED = 2.f; // scale = EXPLOSION_ANIMATION_SCALING_SPEED * progress_of_animation
static constexpr float EXPLOSION_ANIMATION_DURATION = 0.5f; // duration of animation (seconds)

// enemies
static constexpr float ENEMY_SIZE = 80.f;  // size of enemy sprite
static constexpr float ENEMY_SPEED = 60.f; // movement (descend) speed (pixels/s)
static constexpr int MOVING_ENEMY_MAX_HORIZONTAL_SPEED = 100; // horizontal movement speed (pixels/s)
static constexpr int MOVING_ENEMY_MAX_HORIZONTAL_RANGE = 200; // how many pixels to the left and right from original position can the enemy move
static constexpr int MOVING_ENEMY_MIN_HORIZONTAL_RANGE = 50; // how many pixels to the left and right from original position can the enemy move
static constexpr int SHOOTING_ENEMY_MAX_HORIZONTAL_SPEED = 100; // horizontal movement speed (pixels/s)
static constexpr int SHOOTING_ENEMY_MAX_HORIZONTAL_RANGE = 500; // how many pixels to the left and right from original position can the enemy move
static constexpr int SHOOTING_ENEMY_MIN_HORIZONTAL_RANGE = 200; // how many pixels to the left and right from original position can the enemy move
static constexpr int SHOOTING_ENEMY_MAX_Y_POSITION = 300; // distance of the ShootingEnemy from the top of screen
static constexpr int SHOOTING_ENEMY_MIN_Y_POSITION = (int)(ENEMY_SIZE / 2) + 10; // distance of the ShootingEnemy from the top of screen
static constexpr int SHOOTING_ENEMY_MAX_ROCKET_TIME = 10; // time between shooting rockets (seconds)
static constexpr int SHOOTING_ENEMY_MIN_ROCKET_TIME = 1; // time between shooting rockets (seconds)
static constexpr int KILL_SCORE_SIMPLE = 100, KILL_SCORE_MOVING = 100, KILL_SCORE_SHOOTING = 100; // scores for enemy killing

// Sprites
static std::string SPRITES_PATH = "data/sprites/";

// UI
// Font
static std::string FONT_PATH = "data/font/MajorMonoDisplay-Regular.ttf";

// Energy Bar
static constexpr int ENERGY_BAR_WIDTH = 150;
static constexpr int ENERGY_BAR_HEIGHT = 30;
static constexpr int ENERGY_BAR_X = SCREEN_WIDTH - ENERGY_BAR_WIDTH - 10;
static constexpr int ENERGY_BAR_Y = 10;
// Score Text
static constexpr int SCORE_TEXT_WIDTH = 140;
static constexpr int SCORE_TEXT_HEIGHT = 30;
static constexpr int SCORE_TEXT_Y = 5;
extern int SCORE_TEXT_X;

#endif