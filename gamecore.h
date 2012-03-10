/*===================================================================
 * A note one events: 
 *	Any GameEnvironment that uses events must, upon receiving an 
 *  SDL_QUIT event, must either return null from its run() function,
 *  or push the SDL_QUIT event back onto the event queue. 
 *
 *
 *
 *
 */

#ifndef GAMECORE_H
#define GAMECORE_H

#include "constants.h"
#include "GameEnvironment.h"

// returns 0 if successful, or an error code if not
int gameInitialize();

// The Gamecore becomes the owner of the object you pass in.
// Don't do anything except construct the GameEnvironment object. 
void gameRun(GameEnvironment * firstEnvironment);

void gameClose();

#endif 