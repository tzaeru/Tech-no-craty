#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "../include/main.h"
#include "../include/object.h"
#include "../include/generic_object.h"

class Platform : public Object {
	private:
		GLuint world_tex;
		
		GLuint display_list;
		
		vector < Object *> objects;

	public:
		Platform(float xx, float yy, int time_now);
		void Render();
		void Move(int time_now, float grav);
};

#endif
