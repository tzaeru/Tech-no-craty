#include "../include/generic_object.h"

void GenericObject::Render() {
	glBindTexture(GL_TEXTURE_2D,texture);

	glPushMatrix();

	/* Moves the particle to right position */
	glTranslatef(location[0], location[1], location[2]);

	size = 0.5;
	glScalef(size, size, size);

	glDisable(GL_LIGHTING);
	
	glEnable(GL_BLEND);

		/* Draws a textured particle quad */
	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 4 (Front)
	glEnd();	
	
	/* Returns the old view matrix */
	glPopMatrix();
}

void GenericObject::Move(int time_now, float grav) {
	
	last_tick = time_now;

	rotation[2] = sin(time_now/200.)*30;
	
	location[0] = sin(time_now/400.)*0.1;
	
	location[1] = cos(time_now/300.)*0.1;
}

GenericObject::GenericObject(float xx, float yy, float zz, int time_now, string texture_name) {
	
	location[0] = xx;
	location[1] = yy;
	
	last_tick = time_now;
	
	size = 0.25;
	
	LoadTexture(1, texture_name);
}

void GenericObject::CollisionDetection(Object * collider, int time_now)
{
	/* Getting the parameters of colliding object (particle in every case).
	In this implemention the location and velocity parameters of the colliding
	object are pointers - Thus so that this single function may alter the
	velocities of both objects, which is much more optimal for particle
	handling. */
	float * collider_location[3];
	collider->GetLocation(collider_location);
		
	float * collider_velocity[6];
	collider->GetVelocities(collider_velocity);
	
	/* A simple optimization to reduce the amount of particles being checked */
	if (*collider_location[0] - location[0] < 0.5 && *collider_location[0] - location[0] > -0.5 &&
			*collider_location[1] - location[1] < 0.5 && *collider_location[1] - location[1] > -0.5)
	{
	
	float collider_projected_loc[3];
	for (int i = 0; i < 3; i++)
		collider_projected_loc[i] = *collider_location[i] - location[i];
	
	float collider_projected_velocity[6];
	for (int i = 0; i < 6; i++)
		collider_projected_velocity[i] = *collider_velocity[i];

	/* Applies the projection, using waterwheel as the orego */
	ApplyProjection(collider_projected_loc, collider_projected_velocity);

	float collider_next_loc[3];
	collider_next_loc[0] = collider_projected_loc[0] + collider_projected_velocity[0] * ((time_now - last_tick)/1000.);
	collider_next_loc[1] = collider_projected_loc[1] + collider_projected_velocity[1] * ((time_now - last_tick)/1000.);
	collider_next_loc[2] = collider_projected_loc[2] + collider_projected_velocity[2] * ((time_now - last_tick)/1000.);
	
	/*Beginning the collision detection */
	
	/* Check if the particle can be close enough to the object for any collision */
	if (collider_projected_loc[0] <= size && collider_projected_loc[0] >= -size)
		if (collider_projected_loc[1] >= 0 && collider_next_loc[1] <= 0)
		{
			/*
			*collider_velocity[1] = 0;
			*collider_location[1] = location[1];
			*/
			
			/* Velocity of rotation increased slightly with each hit */
			velocity[5] = velocity[5] - 0.005;
			
			/* Calculating the new velocity of the particle that collider */
			float total_velocity = *collider_velocity[1] + *collider_velocity[0];
			
			total_velocity *= 0.4;
			
			*collider_velocity[0] = total_velocity * sin((rotation[2]*2) * DEG_TO_RAD) * 0.8;
			*collider_velocity[1] = total_velocity * fabs(sin((rotation[2]*2) * DEG_TO_RAD)) * 0.8;
			
			/* Setting the new location of the particle */
			*collider_location[1] = location[1] + ((collider_projected_loc[0] * sin((rotation[2]*2) * DEG_TO_RAD)));
			
		}
		//velocity[5] = 4;
}
}
