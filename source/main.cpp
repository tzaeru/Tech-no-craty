#include "../include/main.h"
#include "../include/lua_engine.h"
#include "../include/application.h"

/* Initializes OpenGL */
void initGL();

int WIDTH;
int HEIGHT;

/* The script engine */
LuaEngine* lua_engine;

/* Basic program info */
program_info pInfo;

void LoadConf();

/* The time affected by rewinding, seeking, so on, and used internally. */
int time_now;
/* The actual real time. */
int real_time;

/* Flag for whether seeking should be applied. 0 = no seeking. 1 = seek left. 2 = seek right*/
int seeking = 0;

int main(int argc, char *argv[]){
	/* The starting point of time counting */
	int timer_start = SDL_GetTicks();
	
	SDL_Event event;
	
	LoadConf();
	
	/* Creates the application process, which is initializes and
	 * creates a window, 3D environment, so on.
	 * In this case, we're creating a Qt environment. */
  initGL();
	
  /* Random generator initialization */
	srand ( time(NULL) );

	/* Initialize a script engine, Lua in this case */
	lua_engine = new LuaEngine();
	
	/* Load a script for the engine */
	lua_engine->LoadLuaScript("data/scripts/technocracy.lua");
	
	/* Updating the timers start to now. */
	timer_start = SDL_GetTicks();
  /* Updating the local time to 0, as initialization might take time. */
  time_now = SDL_GetTicks() - timer_start;
	/* Updating the real time to start from now. */
	real_time = SDL_GetTicks() - timer_start;
  
	/* runs until done==1*/
  int done;
  for(done = 0; !done;){
		/* Updating the real time.*/
		real_time = SDL_GetTicks();
		
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glTranslatef(0.0f,0.0f,-0.0f);

		/* Runs the whole .. everything */
		lua_engine->Run(time_now);

    SDL_GL_SwapBuffers();
    SDL_PollEvent(&event);
		
		/* Poll SDL events as long as there's any left and do seeking with LEFT and RIGHT arrow */
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
												seeking = 1;
                        break;
										case SDLK_RIGHT:
												seeking = 2;
												break;
                    case SDLK_ESCAPE:
                        done = 1;
												break;
                    default:
                        break;
                }
							break;
						case SDL_KEYUP:
							seeking = 0;
							break;
            }
        }
		if (seeking == 1)
			time_now -= (SDL_GetTicks() - real_time ) * 5;
		if (seeking == 2)
				time_now += (SDL_GetTicks() - real_time ) * 3;
		else
			time_now += SDL_GetTicks() - real_time;
	}

	delete lua_engine;
  SDL_Quit();
	cout<<"Classes and libraries DESTROYED succesfully!\n";
  return(0);
}

void LoadConf()
{
	string temp;
	char temp2[666];

	fstream file("data/conf.txt", ios::in);

	stringstream parameter;

	if (file == NULL)
	{
		std::cout<<"Couldn't open file data/conf.txt\n";
	}
	else
		while (!file.eof())
		{
			file.getline(temp2, 666);
			temp = temp2;
			string::size_type loc = temp.find("width", 0);
			if (loc != string::npos)
			{
				temp.erase(0, 6);
				pInfo.width = atoi (temp.c_str());
				WIDTH = pInfo.width;
				continue;
			}
			loc = temp.find("height", 0);
			if (loc != string::npos)
			{
				temp.erase(0, 7);
				pInfo.height = atoi (temp.c_str());
				HEIGHT = pInfo.height;
				cout<<atoi (temp.c_str())<<"\n";
				continue;
			}
			
			loc = temp.find("bpp", 0);
			if (loc != string::npos)
			{
				temp.erase(0, 4);
				pInfo.bpp = atoi (temp.c_str());
				continue;
			}
			
			loc = temp.find("name", 0);
			if (loc != string::npos)
			{
				temp.erase(0, 5);
				pInfo.name = temp;
				continue;
			}
		}
		
	file.close();
}

/* Initializes the OpenGL */
void initGL()
{
	SDL_Init(SDL_INIT_VIDEO);
  SDL_SetVideoMode(WIDTH, HEIGHT, 0, SDL_OPENGL);
	
	glEnable(GL_TEXTURE_2D);
  glClearColor(0.0f, 0.0f, 0.0f, -0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW);
  
  glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	SDL_WM_SetCaption( pInfo.name.c_str(), 0 );
}
