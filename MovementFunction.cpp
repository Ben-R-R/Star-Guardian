#include "MovementFunction.h"

void MovementFunction::update(unsigned int frameTime){
	/*The default movement function does nothing except add
	frame time to t*/

	t += frameTime;

}

void MovementFunction::setValue(int t){
	this->t = t;
}