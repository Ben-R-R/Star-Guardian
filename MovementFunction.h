/*
Movement function!!
Created by Ben-R-R


*/

#ifndef MOVEMENTFUNCTION_H
#define MOVEMENTFUNCTION_H

class MovementFunction{
private:
	/*Elapsed time since the start of this move function */
	unsigned int t;
public:

	float x;
	float y;

	void setValue(int t);

	/*
	Pass the time since the last call to this method. 
	*/
	void update(unsigned int frameTime);
}

#endif