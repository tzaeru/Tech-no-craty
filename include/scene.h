/* Scene is a class that handles all the objects in the world. */

#ifndef SCENE_H_
#define SCENE_H_

#include "../include/main.h"
#include "../include/particle.h"
#include "../include/generic_object.h"
#include "../include/audio.h"

class Scene {
	private:
		/* All particle objects belonging to the scene */
		vector < Object *> particles;
		/* Lifetimes of the particles */
		vector < int[2] > particle_lifetimes;

		/* All other objects belonging to the scene */
		vector < Object *> objects;
		/* One lifetime is a simple struct. */
		struct Lifetime {
      int begin;
      int end;
      };
		/* Lifetimes of the objects */
		vector < Lifetime > object_lifetimes;

		/* The local time inside the scene, re-set on each frame */
		int local_time;

		/* Texture for particles */
		GLuint particle_tex;
		
		/* For loading the texture for particles */
		void LoadParticleTexture();

		/* Original author Lauri Kenttä "metabolix", used due to laziness and to save work (guess open source is awesome) */
		int MySDL_glTexImage2D(SDL_Surface *kuva);
		
		/* Strength of gravity */
		float gravity;

public:
	/* Audio object for the scene. Access it directly, e.g. scene->audio.play and so on.
	 * Audio.h for more info.
	 */
	Audio audio;

	/* Initializes scene and sets the local_time variable */
	Scene(int time_now);
		
	/* Destructor */
	~Scene();
		
	/* Create object */
	/* Type = One of object types. 0 stands for generic_object. This is the only type implemented at the moment.
	 * xx, yy, zz = location
	 * time_now = old shit. to be removed. just the current time in milliseconds.
	 * texture = texture of the object
	 * lifetime1, lifetime2 = the beginning and the ending of when the object is supposed to be rendered.
	 */
	int CreateObject(int type, float xx, float yy, float zz, int time_now, string texture, int lifetime1, int lifetime2);
		
	/* Create a set of particles */
	/* start_x = Start of particle shower alongst x-axis.
		 * start_y = Start of particle spread alongst y-axis.
		 * end_x = width of particle shower.
		 * end_y = height of particle shower.
		*/
	int CreateParticles(float start_x, float start_y, float end_x, float end_y, int amount, float xx, float yy,
		float zz, string texture);
		
	/* Create a platform, special kind of an object */
	int CreatePlatform(float xx, float yy, int time_now);
		
	/* Runs the whole scene
	time_now is imput for local time */
	void Run(int time_now);
		
	/* Getting the pointer to the mother scene object */
	Scene *GetScene() { return this; };
};

#endif
