#include "../include/platform.h"

void Platform::Render() {
	
		
		glPushMatrix();
	
	glTranslatef(-0.5, 0.5, 0.0);
	
	glColor4f(1, 1, 1, fabs(cos(last_tick/242.0)));
	objects[0]->Render();
	
	glColor4f(1, 1, 1, fabs(-cos(last_tick/266.0)));
	objects[1]->Render();
	
	glColor4f(1, 1, 1, fabs(cos(last_tick/250.0)));
	objects[2]->Render();
	
	glColor4f(1, 1, 1, -sin(last_tick/325.0));
		glPushMatrix();
		glTranslatef(sin(last_tick/1000.0)*0.01, cos(last_tick/1000.0)*0.01, 0);
		objects[3]->Render();
	glPopMatrix();
	
	glColor4f(2, 2, 2, 2);
	
	glPopMatrix();
	
	
	glBindTexture(GL_TEXTURE_2D,world_tex);					// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH/2, 0, WIDTH/2, HEIGHT, 0);


	//glClearColor(0.1f, 0.0f, 0.025f, 0.05);						// Set The Clear Color To Medium Blue
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And Depth Buffer
	
		
glViewport(0, 0, WIDTH/2, HEIGHT);
	
	 gluPerspective(45.0f,(GLfloat)WIDTH/(GLfloat)HEIGHT,0.0f,100.0f);
		glTranslatef(0.0f,0.0f,-3.0f);

	/* Saves the old view matrix */
	glPushMatrix();
	/* Moves the platform to right position */
	glTranslatef(location[0], location[1], location[2]);
	size = 0.05;
	/* Sets the platform size. */
	glScalef(size, size, size);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);

double dist = sqrt(1 / 3.0);

	gluLookAt(dist, dist, dist,  /* position of camera */
          0.0,  0.0,  0.0,   /* where camera is pointing at */
         0.0,  1.0,  0.0);  /* which direction is up */
	glMatrixMode(GL_MODELVIEW);
	
	glRotated(270, 1, 0, 0);
	
	float movement = 0.025;
	
	glTranslatef((-1.4/movement), -1/movement, 0);

	for (float i = 0; i < 1; i += movement)
	{
		glTranslatef(2+fabs((sin(last_tick/1500.0)*0.8)), 0, 0);
		glPushMatrix();
		for (float j = 0; j < 1; j += movement)
	{
			glTranslatef( 0, 2+0.8,  sin((int)(j*20))*0.5);
			glBindTexture(GL_TEXTURE_2D,world_tex);

	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(i, j); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
		glTexCoord2f(i+movement, j); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
		glTexCoord2f(i+movement, j+movement); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
		glTexCoord2f(i, j+movement); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 4 (Front)
		
		
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(i+movement, j); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Back)
		glTexCoord2f(i+movement, j+movement); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 2 (Back)
		glTexCoord2f(i, j+movement); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 3 (Back)
		glTexCoord2f(i, j); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 4 (Back)
		
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(i, j+movement); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 1 (Top)
		glTexCoord2f(i, j); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 2 (Top)
		glTexCoord2f(i+movement, j); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Top)
		glTexCoord2f(i+movement, j+movement); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 4 (Top)
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(i+movement, j+movement); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
		glTexCoord2f(i, j+movement); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
		glTexCoord2f(i, j); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 3 (Bottom)
		glTexCoord2f(i+movement, j); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 4 (Bottom)
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(i+movement, j); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 1 (Right)
		glTexCoord2f(i+movement, j+movement); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 2 (Right)
		glTexCoord2f(i, j+movement); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Right)
		glTexCoord2f(i, j); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 4 (Right)
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(i, j); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Left)
		glTexCoord2f(i+movement, j); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 2 (Left)
		glTexCoord2f(i+movement, j+movement); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 3 (Left)
		glTexCoord2f(i, j+movement); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 4 (Left)
		
		
	glEnd();
glBindTexture(GL_TEXTURE_2D,0);
glColor4f(0.2, 0.2, 0.2, 0.2);
	glBegin(  GL_LINE_STRIP);
		// Front Face
		glVertex3f(-1.02f, -1.02f,  1.02f);	// Point 1 (Front)
		glVertex3f( 1.02f, -1.02f,  1.02f);	// Point 2 (Front)
		glVertex3f( 1.02f,  1.02f,  1.02f);	// Point 3 (Front)
		glVertex3f(-1.02f,  1.02f,  1.02f);	// Point 4 (Front)
		glVertex3f(-1.02f, -1.02f,  1.02f);	// Point 1 (Front)
		
				
		
				// Bottom Face
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
		glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
		glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 3 (Bottom)
		glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 4 (Bottom)
		glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)


			// Right face
	  glVertex3f( 1.02f, -1.02f, -1.02f);	// Point 1 (Right)
		glVertex3f( 1.02f,  1.02f, -1.02f);	// Point 2 (Right)
	  glVertex3f( 1.02f,  1.02f,  1.02f);	// Point 3 (Right)
		glVertex3f( 1.02f, -1.02f,  1.02f);	// Point 4 (Right)
		glVertex3f( 1.02f, -1.02f, -1.02f);	// Point 1 (Right)
		

				glEnd();
		}
		glPopMatrix();
	}
	glColor4f(1, 1, 1, 1);
	/* Returns the old view matrix */
	glPopMatrix();

/*
	glBindTexture(GL_TEXTURE_2D,world_tex+1);					// Bind To The Blur Texture

	// Copy Our ViewPort To The Blur Texture (From 0,0 To 128,128... No Border)
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, WIDTH, HEIGHT, 0);

	glDisable(GL_LIGHTING);

	glColor4f(0.3, 0.2, 0.2, 0.001);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
	for (int i = 0; i < 10; i++)
	{
	glBegin(GL_QUADS);
	
		glScalef(1.01, 1.01, 1.01);

		glTexCoord2f(0, 0); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
		glTexCoord2f(1, 0); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
		glTexCoord2f(1, 1); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
		glTexCoord2f(0, 1); glVertex3f(-1.0f, 1.0f,  1.0f);	// Point 4 (Front)

	glEnd();
}
	
	glColor4f(1, 1, 1, 1);
*/

	glViewport(WIDTH/2, 0, WIDTH/2, HEIGHT);
}

void Platform::Move(int time_now, float grav) {
	
	last_tick = time_now;

}

Platform::Platform(float xx, float yy, int time_now)
{
	GLuint display_list = glGenLists(1);
	glNewList(display_list, GL_COMPILE);
	
		/* Draws a textured particle quad */
	glBegin(GL_QUADS);
		// Front Face
		glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 4 (Front)
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Back)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 2 (Back)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 3 (Back)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 4 (Back)
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 1 (Top)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 2 (Top)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Top)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 4 (Top)
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 3 (Bottom)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 4 (Bottom)
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 1 (Right)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 2 (Right)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Right)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 4 (Right)
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Left)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 2 (Left)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 3 (Left)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 4 (Left)
	glEnd();	
	
		
	glEndList();

	
	
	
	
	
	
	
	
	
	location[0] = xx;
	location[1] = yy;
	
	last_tick = time_now;
	
	size = 1;
	
	int tex_size_x = 768;
	int tex_size_y = 1024;
	
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((tex_size_x * tex_size_y)* 4 * sizeof(unsigned int))];
	
	data = (unsigned int*)memset(data, 0, ((tex_size_x * tex_size_y)* 4 * sizeof(unsigned int)));
	
	glGenTextures(2, &world_tex);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, world_tex);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, tex_size_x, tex_size_y, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, data);						// Build Texture Using Information In data
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data
	
	
	Object * TObject = new GenericObject(0, 0, 0, last_tick, "data/jester1.png");
	objects.push_back(TObject);
	
	TObject = new GenericObject(0, 0, 0, last_tick, "data/jester2.png");
	objects.push_back(TObject);
	
	TObject = new GenericObject(0, 0, 0, last_tick, "data/jester3.png");
	objects.push_back(TObject);
	
	TObject = new GenericObject(0, 0, 0, last_tick, "data/jester4.png");
	objects.push_back(TObject);
}
