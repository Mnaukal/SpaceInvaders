/*
	InvadersConstants.hpp - all numeric constants for Invaders Game - player size, speed, ...
*/

#ifndef constants_hpp_
#define constants_hpp_

#include "SFML/Graphics.hpp"

// Invaders
static constexpr int SCREEN_WIDTH = 1280; // width of game window
static constexpr int SCREEN_HEIGHT = 720; // height of game window

// player
static constexpr float PLAYER_SIZE = 50.f;  // size of player sprite
static constexpr float PLAYER_SPEED = 300.f; // movement speed (pixels/s)
static constexpr float PLAYER_START_POSITION_X = SCREEN_WIDTH / 2; // player starts at horizontal center of screen
static constexpr float PLAYER_START_POSITION_Y = SCREEN_HEIGHT - PLAYER_SIZE / 2; // player starts at down edge of screen


// rockets
static constexpr float ROCKET_SIZE_X = 10.f; // size of rocket sprite
static constexpr float ROCKET_SIZE_Y = 45.f; // size of rocket sprite
static constexpr float ROCKET_SPEED = 500.f; // movements speed (pixels/s)

// explosions (animation)
static constexpr float EXPLOSION_SIZE = 80.f;  // size of player sprite
static constexpr float EXPLOSION_ANIMATION_SCALING_SPEED = 2.f; // scale = EXPLOSION_ANIMATION_SCALING_SPEED * progress_of_animation
static constexpr float EXPLOSION_ANIMATION_DURATION = 0.5f; // duration of animation (seconds)

// enemies
static constexpr float ENEMY_SIZE = 80.f;  // size of enemy sprite
static constexpr float ENEMY_SPEED = 100.f; // movement (descend) speed (pixels/s)

#endif