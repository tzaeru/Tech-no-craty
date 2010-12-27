#ifndef GENERICOBJECT_H_
#define GENERICOBJECT_H_

#include "../include/main.h"
#include "../include/object.h"

class GenericObject : public Object {
		public:
			GenericObject(float xx, float yy, float zz, int time_now, string texture_name);
			void Render();
			void Move(int time_now, float grav);
			
			void CollisionDetection(Object * object, int timenow);
};

#endif
