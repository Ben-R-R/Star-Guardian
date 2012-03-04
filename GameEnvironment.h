#ifndef GAMEENVIRONMENT_H
#define GAMEENIVRONMNET_H

class GameEnvironment{
public:
	/* Returns the success of the initialization */
	virtual bool init() = 0;

	/* Called once when you start regular calls to run()*/
	virtual void enter() = 0;
	
	/* returns the environment that should be called next tick
	the calling function does not need to worry about calling 
	any of the housekeeping methods for the returned object
	or the current object. 
	
	if this method returns a different GameEnvironment, the
	current one is only guaranteed to stay in memory until
	the next call to run. In general calling classes are 
	only responsible for the memory of the current 
	game object. 
	
	Conversely, extending classes must be careful to insure that
	memory gets properly de-allocated if they return an object 
	besides themselves */
	virtual GameEnvironment* run(unsigned int tickTime) = 0;

	/* Called once after you stop making regular calls to run()
	Usually handled by another GameEnvironment class.*/
	virtual void exit() = 0;

	virtual ~GameEnvironment() = 0;
};



#endif