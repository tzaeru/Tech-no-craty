/* The animation class.
 * This class is supposed to be bound
 * with any possible variable, either a
 * table, some STL container or
 * a single variable of any value type.
 */

#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "../include/main.h"

class Animation {
private:
	/* These are variables of type float
	 * bound to the Animation object.
	 * 
	 */
	vector < float *> bound_floats;
	
	
public:
	Animation(float * value);
	//Animation(int n, float * values[]);
	~Animation();
	
	/* The method that actually modifies/animates the bound value. */
	void Animate();
};

#endif