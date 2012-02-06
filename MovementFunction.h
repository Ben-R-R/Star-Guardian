/* =========================================================================
MovementFunction.h

Author(s):
	Ben-R-R

Description:
	Contains declarations of the various classes used to 
	move objects. 

	As a convention, classes that extend MovementFunction 
	will be prefixed with "MF_"

Dependencies:
	SDL.h
	eventListener.h

Classes:
	MovementFunction
	MF_Linear
	MF_Polar
=============================================================================*/

#ifndef MOVEMENTFUNCTION_H
#define MOVEMENTFUNCTION_H

#include "eventListener.h"
#include "SDL.h"

/*===================================================================
MovementFunction: This is a Base class designed to provide a
minimal position interface for more complex classes.

Author(s)
	Ben-R-R
===================================================================*/
class MovementFunction{
protected:
	/* Elapsed time since the start of this move function */
	unsigned int t;

	EventListener* eListener;

	int eventNum;

	/* update the position stored in rectPos */
	void setSDL_RecPos();

	/*Checks the current position against the set bounds. 

	calls eListener::doEvent(eventNum) if the object is outside 
	the given bounds. 

	Should be called from update() after the x and y values 
	are updated.*/
	bool checkBounds();

public:
	/* Rectangle position used in drawing with the SDL library, only the x and y 
	values are guaranteed to be meaningful. */
	SDL_Rect rectPos;
	
	float x;
	float y;

	virtual void setBoundsListener(EventListener* listener, int eventNumber);
	
	virtual void setBounds(float x, float y, float width, float height);

	virtual ~MovementFunction();

	virtual MovementFunction* clone(const MovementFunction& mf);
	
	/* ==========  setTimeElapsed ==================
	Sets the elapsed time. May or may not have effects 
	for derived classes. 

	Arguments: 
		unsigned int t
	*/
	virtual void setTimeElapsed(unsigned int t);
	
	/* ==========  default constructor  ============
	Zero initializes everything */
	MovementFunction();

	MovementFunction(float x, float y);

	/* ==========  update  =========================
	The default update function does nothing except add
	frame time to t.

	Arguments:
		unsigned int frameTime  -  The amount of time you want to 
			advance the function, usually the time since the last 
			call to this function. */
	virtual void update(unsigned int frameTime);
};

/*============  MF_Linear  ==========================================
Linear Movement Function: moves the object in a straight line. 
Provides various convenient construction methods. Tastes good 
marinated in red vinegar.

Author(s)
	Ben-R-R
===================================================================*/
class MF_Linear: public MovementFunction{

protected:
	float xPerMilli;
	float yPerMilli;

	float xStart;
	float yStart;

public:
	
	virtual ~MF_Linear();

	/* ========== Inherited Functions ================*/

	virtual void update(unsigned int frameTime);

	/* Using this function will also set the position
	of the object relative the coordinates given during 
	construction. */
	virtual void setValue(int t);
	
	/* ==========  Empty Constructor ===============
	Initializes everything to zero */
	MF_Linear();

	/* ==========  Cartesian constructor  ==========
	Arguments:
	float x  -  starting x position
	float y  -  starting y position
	float xPerSec  -  change in x each second
	float yPerSec  -  change in y per second */
	MF_Linear(float x, float y, float xPerSec, float yPerSec);

	/* ==========  Polar Constructor ==============
	Arguments:
	float x  -  starting x position
	float y  -  starting y position
	float angle  -  angle of movement
	float speed  -  speed in pixels per second
	bool radians  -  provide true if the angle argument should be 
					 interpreted as radians, false if it should be
					 interpreted as degrees. */
	MF_Linear(float x, float y, float angle, float speed, bool radians);

};

/*===================================================================
Polar Function Wrapper. Takes a movement function and converts it from 
Polar to Cartesian coordinates, interpreting x as the radius and y as 
the angle. The origin is defined by another given movement function. 

Author(s)
	Ben-R-R
===================================================================*/
class MF_Polar: public MovementFunction{
protected:
	MovementFunction coords;
	MovementFunction radiaus;
public:
	virtual ~MF_Polar();
	virtual update();
	MF_Polar();
	MF_Polar(const MovementFunction& coords, const MovementFunction& origin);
};

#endif