	#include "../include/particle.h"

Particle::Particle(float xx, float yy, int time_now)
{
	location[0] = xx;
	location[1] = yy;
	location[2] = 0;
	
	/* Saving the original location for 'restarting' the particle */
	original_location[0] = location[0];
	original_location[1] = location[1];
	original_location[2] = location[2];
	
	/* Sets the weight to random between 0.5..1.5
		Creates a bit more interesting particle mess */
	velocity[1] =  -0.5 - ((rand() % 100)/200.);
	
	velocity[0] = 0;
	velocity[2] = 0;
	
	last_tick = time_now;
	
	size = 0.01;
	weight = 0.1;
}

/* Renders the particle.
	Basically it's just a quad with blending on and texture being a filled circle */
void Particle::Render()
{	
	/* Saves the old view matrix */
	glPushMatrix();

	/* Moves the particle to right position */
	glTranslatef(location[0], location[1], location[2]);
	
	/* Sets the particle size. */
	glScalef(size, size, size);

	/* Draws a textured particle quad */
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd();
	
	/* Returns the old view matrix */
	glPopMatrix();
}

void Particle::Move(int time_now, float grav)
{	
	/* The movement alongst y-axis */
	/* Checking how much the particle should have moved between the last and current tick */
	float movement = velocity[1] * ((time_now - last_tick)/1000.);
	
	/* Lets the particle to fall from y-axis point 1 to y-axis point -1 before
		randomizing a new weight and setting the particle back to point 1 */
	if (location[1] - movement < -1.0)
	{
		/* Randomizing a new velocity alongst y-axis */
		velocity[1] =  -0.5 - ((rand() % 100)/200.);
		/* Setting the other velocities to 0 */
		velocity[0] = 0;
		velocity[2] = 0;
		
		
		location[1] = 1.0;
		
		/* Setting the location alongst x- and z -axises to the original it was in creation */
		location[0] = original_location[0];
		location[2] = original_location[2];
	}
	else
		location[1] += movement;

	/* Applying the effects of gravitation */
	velocity[1] -= (grav * weight) * ((time_now - last_tick)/1000.);
	
	/* The movement alongst x-asis */
	location[0] += velocity[0] * ((time_now - last_tick)/1000.);
	
	last_tick = time_now;
}
