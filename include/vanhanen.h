

#include "../include/object.h"

class Vanhanen : public Object {
	public:
		Vanhanen( int time_now);
		void Render();
		void Move(int time_now );
	void smooth( float time );
	static const int WI = 40;
	static const int HE = 30;
	float kakka[WI*HE];
};

