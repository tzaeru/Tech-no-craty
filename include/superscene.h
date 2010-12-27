#ifndef SUPERSCENE_H_
#define SUPERSCENE_H_

#include "../include/main.h"
#include "../include/scene.h"

class Superscene {
private:
	/* Map of scenes with their associated values and pointers */
	map <string, Scene*> scene_map;

	/* The actual scene-objects. */
	vector < Scene > scenes;

public:
	Superscene();
	~Superscene();
	
	Scene* scene;
	
	/* Creates a scene object */
	void NewScene();
	
	/* Run a whole scene */
	void Run(int time_now);
};

#endif