/*============================================================================
 * GameEnvironment.h
 * 
 * Authors:
 *    Ben Reddersen tolkienfan72@gmail.com
 *
 *
 *
 ===========================================================================*/

#ifndef GAMEENVIRONMENT_H
#define GAMEENIVRONMNET_H

#include "constants.h"

/*============================================================================
 * A note one events: 
 *	Any GameEnvironment that uses events must, upon receiving an 
 *  SDL_QUIT event, must either return null from its run() function,
 *  or push the SDL_QUIT event back onto the event queue. 
 *
 * 
 *==========================================================================*/
class GameEnvironment{
public:

	/* Returns true if this GameEnvironment consumes the events on the SDL 
	event queue. This is so that the Gamecore avoids accidentally consuming 
	events that the GameEnvironment might need. Do not return true from this
	method if you are not using events!*/
	virtual bool usingEvents() = 0;

	/* Returns the success of the initialization */
	virtual bool init() = 0;

	/* Called once when you start regular calls to run()*/
	virtual void enter() = 0;
	
	/* returns the environment that should be called next tick
	the calling function does not need to worry about calling 
	any of the housekeeping methods for the returned object
	or the current object. 
	
	In general calling classes are only responsible for the 
	memory of the current game object. 
	
	Conversely, extending classes must be careful to insure that
	memory gets properly de-allocated if they return an object 
	besides themselves */
	virtual GameEnvironment* runTick(unsigned int tickTime) = 0;

	/* All rendering should be done in this function. This function will
	be called even if you return a different GameEnvironment object besides
	yourself.

	This method might not be called if the calling class determines that it would
	take too long. 

	tickTime is the time since the last call to the render. 
	
	*/
	virtual void render(unsigned int tickTime, SDL_Surface &drawSurface) = 0;

	/* Called once after you stop making regular calls to run()
	Usually handled by another GameEnvironment class.*/
	virtual void exit() = 0;

	virtual ~GameEnvironment(){};
};



#endif