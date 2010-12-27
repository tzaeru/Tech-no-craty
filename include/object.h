/* A superclass used for all objects in the world. */

#ifndef OBJECT_H_
#define OBJECT_H_

#include "../include/main.h"
#include "../include/animation.h"

class Object {
	protected:
		/* The last moment in milliseconds when the object was moved */
		int last_tick;

		/* Location of the object. */
		float location[3];

		/* Rotation. */
		float rotation[3];

		/* Size of the object
			Object model themselves should be sized so that
			vertex in the widest axis go from -1 to 1. */
		float size;

		/* The current velocity of object along the three axises and rotation around axises.
		0-2 = x, y, z. 3-5 = rot x, rot y, rot z */
		float velocity[6];

		/* Texture */
		GLuint texture;

		/* For loading the texture */
		/* n = number of the texture. name = filename of the texture */
		int LoadTexture(int n, string name);

		/* Original author Lauri Kenttä "metabolix", used due to laziness and to save work (guess open source is awesome) */
		int MySDL_glTexImage2D(SDL_Surface *kuva);
public:
	/* Constructor & Destructor */
	Object();
	~Object();
	
		/* Accessors */
		inline void GetLocation(float *loc[])
		{ loc[0] = &location[0]; loc[1] = &location[1]; loc[2] = &location[2];}
		
		inline void GetVelocities(float *vel[])
		{ vel[0] = &velocity[0]; vel[1] = &velocity[1]; vel[2] = &velocity[2];
		vel[3] = &velocity[3]; vel[4] = &velocity[4]; vel[5] = &velocity[5];}
		
		inline float GetSize()
		{ return size; }
		
		/* Mutators */
		inline void SetLocation(float *loc[])
		{	location[0] = *loc[0]; location[1] = *loc[1]; location[1] = *loc[1]; }

		inline void SetVelocity(float *vel[])
		{	velocity[0] = *vel[0]; velocity[1] = *vel[1]; velocity[2] = *vel[2]; velocity[3] = *vel[3]; velocity[4] = *vel[4]; velocity[5] = *vel[5];}
		
		/* Function to do projection, related to collision detection.
			target_rotation = read only, rotation of the object that is getting collided.
			collider_locations = read & write, the locations of the colliding object.
			collider_velocities = read & write, the velocities of the colliding object. */
		void ApplyProjection(float *collider_locations, float *collider_velocities);
		
		/* Renders the object */
		virtual void Render() { };
		
		/* Checks collision with another object */
		virtual void CollisionDetection(Object * collider, int time_now) { };
		
		/* Moves the object */
		virtual void Move(int time_now, float grav) { };
};

#endif
