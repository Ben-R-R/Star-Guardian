#ifndef HUD_H
#define HUD_H

#include "constants.h"

// Call this once, before entering game environment
// Calling this multiple times is safe but wasteful
void initHUD();

// Call these while boss appears on screen
void drawBossHUD(SDL_Surface &surface, int health, char* name);
void drawBossHUD(SDL_Surface &surface, int health);
void drawBossHUD(SDL_Surface &surface);

// Call these each tick to display player hud
void drawPlayerHUD(SDL_Surface &surface, int health, int lives);
void drawPlayerHUD(SDL_Surface &surface, int lives);
void drawPlayerHUD(SDL_Surface &surface);

// Alternate to overloaded methods
// Use these to modify values that will be displayed graphically
void changeBossHealthHUD(int health);
void changePlayerHealthHUD(int health);
void changePlayerLivesHUD(int lives);

#endif //HUD_H
