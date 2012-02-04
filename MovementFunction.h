/*
Movement function!!
Created by Ben-R-R


*/

class MoevementFunction{
private:
	/*Elapsed time since the start of this move function */
	unsigned int t;
public:

	float x;
	float y;

	void setValue(int x, int y, int t)

	/*
	Pass the time since the last call to this method. 
	*/
	void update(unsigned int frameTime);
}