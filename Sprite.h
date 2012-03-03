#ifndef SPRITE_H
#define SPRITE_H

#include "constants.h"

#ifdef LINUX
#include <SDL.h>
#else
#include "SDL.h"
#endif

#include <vector>
#include <string>

/* 
======================================================================
CAUTION do not extend this class, as using an extended class will
lead to memory leaks
======================================================================

The basic idea here is we have one big SDL_Surface that has all the tiles on it.

The tiles are indexed left to right, top to bottom, so like so:

+--+---+---+---+
|0 | 1 | 2 | 3 |
+--+---+---+---+
|4 | 5 | 6 | 7 |
+--+---+---+---+
|8 | 9 | 10| 11|
+--+---+---+---+

A frame set is a vector listing tiles the some order like so:

3, 7, 11, 4, 8, 12

So frame 3 in that set would draw tile 4 from the sheet.

Frame set 0, which is provided, is just the tiles listed in their default ordering:

0, 1, 2, 3, etc...

You can add frame sets by calling the addSet() function, and you can set the 
current frame set by calling the setSet function. // Woo! 6 instances of the word 
//'set' in a sentence! A new record!

If your sprite is not animated, just pass 0 as the frameTime when drawing.

*/
class Sprite{
private:
	SDL_Surface* spriteSheet;

	std::vector< std::vector<int> > frameSets;
	
	Sprite(std::string file, const SDL_Rect &frameSize);

	// It would be bad if someone created this class without initializing everything
	// don't do this
	Sprite();

	// don't call this either. Call createNew. Seriously. >_>
	Sprite(SDL_Surface* image, const SDL_Rect &size, int frameTime);

	// if you are reading this header file and not Ben, you don't care about this 
	// function. 
	void updateTimer(unsigned int frameTime); // Done
	
	unsigned int frameIndex;
	unsigned int setIndex;

	unsigned int frameTime;
	unsigned int elapsedTime;

	// the width and height of the frame set image.
	// we use these rather than the spriteSheet width and height functions
	// because we need the nearest smallest multiple of the sprite size to
	// correctly draw the sprite. 
	int w_W;
	int h_H;

	int w_F;
	int h_F;

	SDL_Rect frameSize;

public:
	

	// returns a null pointer if there was an error 
	static Sprite* createNew(std::string file, const SDL_Rect &frameSize, int frameTime);
	 
	
	~Sprite();

	// set the frameset 
	void setSet(int set); 

	void addSet(const std::vector<int> &setVec);

	// sets the frame
	void setFrame(int frame);

	// draws the current frame on the given surface at the given location
	// the units on frame time are milliseconds. 
	void drawCurrent(SDL_Surface *dest,SDL_Rect * location, unsigned int frameTime);


	// draws the given tile at the given location
	void drawTile(SDL_Surface *dest, SDL_Rect * location, unsigned int frameNumber);
};

#endif