/* Some common includes. Using namespace std for practicality. */

#ifndef CREATOR_H_
#define CREATOR_H_

#include <vector>
#include <list>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL_mixer.h>
#include <fstream>
#include <sstream>
#include <map>

#include <QtGui/QApplication>
#include <QtOpenGL/QGLWidget>

#define PI 3.14159265
#define DEG_TO_RAD PI/180.0


/* Which GUI library to use:
 * 1 stands for SDL,
 * 2 stands for Qt
 * 3 stands for both */
enum { UseSDL, UseQt };

extern int WIDTH;
extern int HEIGHT;

using namespace std;

struct program_info{
	string name;
	int width;
	int height;
	int bpp;
};

extern program_info pInfo;

#endif
