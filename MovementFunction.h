/* =========================================================================
MovementFunction.h

Author(s):
	Ben-R-R

Description:
	Contains declarations of the various classes used to 
	move objects. 

	As a convention, classes that extend MovementFunction 
	will be prefixed with "MF_"

	Movement function classes should preserve the values in
	the w and h fields of the rectPos member. This allows 
	users to optimize collision detection by storing values
	in the w and h fields.

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

#include "constants.h"
#include "eventListener.h"

/*============  MovementFunction ====================================
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

	bool boundsSet;

	float boundX;
	float boundY;
	float width;
	float height;

	/*Checks the current position against the set bounds. 

	calls eListener->doEvent(eventNum) if the location is 
	out of bounds.

	Should be called from update() after the x and y values 
	are updated. */
	virtual bool checkBounds();

public:
	/* Rectangle position used in drawing with the SDL library, only the x and y 
	values are guaranteed to be meaningful. */
	SDL_Rect rectPos;
	
	float x;
	float y;

	virtual ~MovementFunction();

	virtual MovementFunction* clone() const;


	virtual void setBoundsListener(EventListener* listener, int eventNumber);
	
	virtual void setBounds(float x, float y, float width, float height);

	
	/* ==========  setTimeElapsed ==================
	Sets the elapsed time. May or may not have effects 
	for derived classes. 

	Arguments: 
		unsigned int t
	*/
	virtual void setTimeElapsed(unsigned int t);

	/* ==========  update  =========================
	The default update function does nothing except add
	frame time to t.

	Arguments:
		unsigned int frameTime  -  The amount of time you want to 
			advance the function, usually the time since the last 
			call to this function. */
	virtual bool update(unsigned int frameTime);

	/* ==========  default constructor  ============
	Zero initializes everything */
	MovementFunction();

	/* ==========  position only constructor =======
	sets the position only */
	MovementFunction(float x, float y);
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
	
	virtual MF_Linear* clone() const;

	virtual ~MF_Linear();

	/* ========== Inherited Functions ================*/

	virtual bool update(unsigned int frameTime);

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
	MovementFunction* _coords;
	MovementFunction* _origin;

	virtual void convertCoords();

public:

	MF_Polar();

	MF_Polar( const MF_Polar& other );
	
	/* Clones the input functions */
	MF_Polar(const MovementFunction& coords, const MovementFunction& origin);


	virtual ~MF_Polar();


	virtual MF_Polar* clone() const;

	MF_Polar& MF_Polar::operator=( const MF_Polar& rhs );

	
	virtual bool update(unsigned int framTime);

	virtual void setOrigin(const MovementFunction& origin);

	virtual void setCoords(const MovementFunction& coords);

};



#endif
