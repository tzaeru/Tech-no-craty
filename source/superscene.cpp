#include "../include/superscene.h"

void Superscene::Run(int time_now)
{
	scene->Run(time_now);
}

void Superscene::NewScene()
{
	scene = new Scene(10);
}

Superscene::Superscene()
{
	
}

Superscene::~Superscene()
{
	
}
