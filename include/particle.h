/* Class for particles.
	Particles are handled a bit differently than the other objects by the scene class */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "../include/object.h"
#include "../include/main.h"

class Particle : public Object {
	private:
		float weight;
		float original_location[3];
	public:
		Particle(float xx, float yy, int time_now);
		void Render();
		void Move(int time_now, float grav);
};

#endif
