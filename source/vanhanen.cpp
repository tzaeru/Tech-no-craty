	#include "../include/vanhanen.h"

Vanhanen::Vanhanen(int time_now)
{
	last_tick = time_now;
	for ( int a=0; a<WI*HE; a++ ) kakka[a] = 0;
	LoadTexture( 1, "data/Matti_Vanhanen.jpg" );
}

void Vanhanen::smooth( float time )
{
int q=0;
for ( int a=0; a<HE; a++ )
{
	for ( int b=0; b<WI; b++ )
	{
		float p1 = 0;
		float p2 = kakka[q];
		if ( b>0 ) 
			p1 += kakka[q-1];
		if ( b<WI-1 ) 
			p1 += kakka[q+1];
		if ( a>0 ) 
			p1 += kakka[q-WI];
		if ( a<HE-1 ) 
			p1 += kakka[q+WI];
		float d = (p2*0.8) + (p1/4.0f)*0.2 ;
//		if ( d<0 ) d = 0;
		kakka[q++]= d;
		
	}
}
}

void Vanhanen::Render()
{	

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,1,0,1,-1,2);

	glDisable( GL_CULL_FACE );

	glColor4f(1,1,1,1);

	glBindTexture( GL_TEXTURE_2D, texture );

	glBegin(GL_QUADS);


	float x_ = 1.0f/((float)WI);
	float y_ = 1.0f/((float)HE);
	for ( int a=0; a<HE; a++ )
	{
		for ( int b=0; b<WI; b++ )
		{
			
			int q = a*WI+b;
			float kq1 = kakka[q+1];
			float kq4 = kakka[q];
			float kq3 = kakka[q+WI+1];
			float kq2 = kakka[q+WI];

		kq1 = sin(kq1);
		kq2 = sin(kq2);
		kq3 = sin(kq3);
		kq4 = sin(kq4);


		float x1 = a*x_;
		float x2 = x1+x_;
		float y1 = b*y_;
		float y2 = y1+y_;

		glTexCoord2f( x1 + kq1, y1 + kq1 ); 
		glVertex3f( x1, y1, 1.0f);
		glTexCoord2f( x2 + kq2 , y1 + kq2 ); 
		glVertex3f( x2, y1, 1.0f);
		glTexCoord2f( x2 + kq4, y2 + kq4); 
		glVertex3f( x2, y2, 1.0f);
		glTexCoord2f( x1 + kq3, y2 + kq3); 
		glVertex3f( x1, y2, 1.0f);
	}
	}
	glEnd();
	
	/* Returns the old view matrix */
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}

void Vanhanen::Move(int time_now )
{	
	smooth( time_now - last_tick );
	last_tick = time_now;

//if ( (rand()%10) == 1 ) 
	kakka[rand()%(WI*HE)]+=0.4f;
}
