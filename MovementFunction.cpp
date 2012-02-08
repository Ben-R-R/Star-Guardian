/* =========================================================================
MovementFunction.h

Author(s):
	Ben-R-R

Description:
	Contains definitions of the various classes in "MovementFunction.h"

	In general, look in the header file for comments on using the functions
	in this file. Comments here are related only to the technical details of
	implementation.

Dependencies:
	MovementFunction.h
	math.h
	constants.h
=============================================================================*/

#include "MovementFunction.h"

#include <math.h>
#include "constants.h"

/*====================================
	class MovementFunction
=====================================*/

/* Constructors */

MovementFunction::MovementFunction()
	: rectPos(), 
	x(0),
	y(0)
{}

MovementFunction::MovementFunction(float X, float Y)
	: rectPos(), 
	x(X), // sorry for the odd syntax, can't use 'this' here 
    y(Y)
{
	rectPos.h = 1;
	rectPos.w = 1;
	rectPos.x = int(X + 0.5); // float conversion with rounding
	rectPos.y = int(Y + 0.5);
}

/* housekeeping */

MovementFunction* MovementFunction::clone() const{
	return new MovementFunction(*this);
}

MovementFunction::~MovementFunction()
{ }

/* No need to implement the destructor */

/* protected functions */

bool MovementFunction::checkBounds(){
	
	
	if((x < boundX || x > boundX + width || y < boundY || y > boundY + width) && eListener){
		eListener->doEvent(eventNum);
		return true;
	}
	return false;
}

void MovementFunction::setSDL_RecPos(){
	rectPos.x = int(x + 0.5);
	rectPos.y = int(y + 0.5);
}

/* public functions */

void MovementFunction::setBoundsListener(EventListener* listener, int eventNumber){
	eListener = listener;
	eventNum = eventNumber;
}

void MovementFunction::setBounds(float x, float y, float width, float height){
	this->boundX = x;
	this->boundY  = y;

	/* deal harshly with negative values. */
	if(width < 0){
		x = x + width;
		width = -width;
	}

	if(height < 0){
		y = y + height;
		height = -height;
	}

	this->width = width;
	this->height = height;
}

bool MovementFunction::update(unsigned int frameTime){
	t += frameTime;
	
	setSDL_RecPos();
	return checkBounds();
}

void MovementFunction::setTimeElapsed(unsigned int t){
	this->t = t;
}


/*====================================
	class MF_Linear
=====================================*/

/* Constructors */

MF_Linear::MF_Linear(): MovementFunction() {};

MF_Linear::MF_Linear(float x, float y, float xPerSec, float yPerSec)
	: MovementFunction(x, y)
{
	
	this->xPerMilli = xPerSec / 1000;
	this->yPerMilli = yPerSec / 1000;
}

MF_Linear::MF_Linear(float x, float y, float angle, float speed, bool radians)
	: MovementFunction(x, y) 
{
	if(!radians){
		
		angle = angle * (PI_f / 180);
	}

	this->xStart = x;
	this->yStart = y;

	this->xPerMilli = sin(angle) * (speed / 1000);
	this->yPerMilli = cos(angle) * (speed / 1000);


}

/* Housekeeping */

MF_Linear* MF_Linear::clone() const{
	return new MF_Linear(*this);
}

MF_Linear::~MF_Linear()
{ }

/* Virtual function overrides */

bool MF_Linear::update(unsigned int frameTime){

	x += xPerMilli * frameTime;
	y += yPerMilli * frameTime;

	// checks bounds and updates the SDL position 
	return MovementFunction::update(frameTime);

	

}

void MF_Linear::setValue(int t){
	this->t = t;
	x = xPerMilli * this-> t + xStart;
	y = yPerMilli * this->t + yStart;

}

/*====================================
	class MF_Polar
=====================================*/

/* empty constructor */
MF_Polar::MF_Polar()
	
{
	_coords = new MovementFunction(0,0);
	_origin = new MovementFunction(0,0);
}

/* Copy constructor */
MF_Polar::MF_Polar( const MF_Polar& other )
	: MovementFunction(other)
{
	_coords = (*other._coords).clone();
	_origin = (*other._origin).clone();
}

/* main constructor */
MF_Polar::MF_Polar(const MovementFunction& coords, const MovementFunction& origin)
    : MovementFunction()
{
	_coords = coords.clone();
	_origin = origin.clone();
}

/* Destructor */
MF_Polar::~MF_Polar(){
	delete _coords;
	delete _origin;
}

MF_Polar& MF_Polar::operator=( const MF_Polar& rhs ){
	if(this ==  &rhs){
		return *this;
	}


	MovementFunction::operator=(rhs);


	delete _coords;
	delete _origin;

	_coords = (*rhs._coords).clone();
	_origin = (*rhs._origin).clone();

	return *this;
}


/* Clone, same as the other clone functions. The party's in the copy constructor */
MF_Polar* MF_Polar::clone() const {
	return new MF_Polar(*this);

}



bool MF_Polar::update(unsigned int t){
	_coords->update(t);
	_origin->update(t);

	convertCoords();
	
	setSDL_RecPos();
	return checkBounds();
}

void MF_Polar::convertCoords(){
	x = cos(_coords->y) * _coords->x + _origin->x;
	y = sin(_coords->y) * _coords->x + _origin->y;
}

void MF_Polar::setOrigin(const MovementFunction& origin){
	delete _origin;
	
	_origin = origin.clone();
}


void MF_Polar::setCoords(const MovementFunction& coords){
	delete _coords;
	
	_coords = coords.clone();

}