#include "../include/scene.h"

#include "../include/platform.h"

/* Running the scene means first updating the local time,
	then moving all the objects and checking for collisions,
	and finally rendering the objects to the screen */
void Scene::Run(int time_now)
{
	local_time = time_now;
	
	/* Iterate through particles, check potential collisions
		and finally move the particle.
		Particles are handled separately because they do not
		collide with themselves. */
	
	//glViewport(WIDTH/2, 0, WIDTH/2, HEIGHT);
		
	for (int i = 0; i < particles.size(); i++)
	{
		for (int j = 0; j < objects.size(); j++)
			objects[j]->CollisionDetection(particles[i], local_time);
		
		particles[i]->Move(local_time, gravity);
	}

	/* Iterate through other objects and move them. */
	glPushMatrix();
	glRotatef(sin(time_now/200.)*30, 0, 1, 0);
		objects[0]->Move(local_time, gravity);
	glPopMatrix();
	
	for (int i = 1; i < objects.size(); i++)
		objects[i]->Move(local_time, gravity);

	/* Iterate through particles and other objects and render them. */
	/* Particles are iterated through first: To save processing power,
	they all have the same OpenGL states set, including the texture.
	For a "real" application this way of doing particles is somewhat
	bad for it's slowness. Geometry shaders should be made use of
	instead or a more efficient particle engine.*/
	glBindTexture(GL_TEXTURE_2D, particle_tex);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	for (int i = 0; i < particles.size(); i++)
		particles[i]->Render();

	/* The other objects have their own unique OpenGL states and textures.*/
	for (int i = 0; i < objects.size(); i++) {
		if (object_lifetimes[i].begin < time_now && object_lifetimes[i].end > time_now)
		{
			objects[i]->Render();
		}
	}
}

/* Loads the texture for particles */
void Scene::LoadParticleTexture()
{
	glGenTextures(1, &particle_tex); 
	glBindTexture(GL_TEXTURE_2D, particle_tex);
	
	SDL_Surface * waterdrop = IMG_Load("data/waterdrop.png");
	
	cout<<MySDL_glTexImage2D(waterdrop)<<"\n";
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	// Linear Filtering
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	// Linear Filtering
	
	SDL_FreeSurface(waterdrop);
}

int Scene::CreateObject(int type, float xx, float yy, float zz, int time_now, string texture, int lifetime1, int lifetime2)
{
	Object *TObject = new GenericObject(xx, yy, zz, local_time, texture);
	objects.push_back(TObject);
	
	Lifetime lifetime;
	lifetime.begin = lifetime1;
	lifetime.end = lifetime2;
	object_lifetimes.push_back(lifetime);
	
	return objects.size() - 1;
}

int Scene::CreatePlatform(float xx, float yy, int time_now)
{
	Object * TObject = new Platform( xx,  yy,  time_now);
	objects.push_back(TObject);

	Lifetime lifetime;
	lifetime.begin = 0;
	lifetime.end = 1000000;
	object_lifetimes.push_back(lifetime);

	return objects.size()-1;
}

/* Generates a load of particles */
int Scene::CreateParticles(float start_x, float start_y, float end_x, float end_y, int amount, float xx, float yy,
float zz, string texture)
{
	float x = start_x;
	float y = start_y;
	/* Generates the particles */
	for (int i = 0; i < amount; i++)
	{
		Object * TObject = new Particle((-1500 + i)/1000., (float) 1, local_time);
		
		particles.push_back(TObject);
	}
	
	return  particles.size() - 1;
}

/* Contructor for scene.
	Takes the current time as input */
Scene::Scene(int time_now)
{
	local_time = time_now;
	
	LoadParticleTexture();
	
	/* Initializes gravity value */
	gravity = 1.0;
	
	cout<<"LOADED\n";
}

/* Destructor */
Scene::~Scene()
{
	particles.clear();
	particle_lifetimes.clear();
	
	objects.clear();
	object_lifetimes.clear();
	
	glDeleteTextures( 1, &particle_tex);
}

/* Function to convert SDL surface into OGL texture, author Lauri Kenttä/"metabolix" */
int Scene::MySDL_glTexImage2D(SDL_Surface *kuva) 
{ 
    SDL_Surface *apu; 
    /* Helpottaa, jos tavut ovat järjestyksessä RGBA. 
     * Säädetään siis konetyypin mukaan värien bittimaskit 
     * niin, että tavujen järjestys muistissa osuu oikein. */ 
#if SDL_BYTEORDER == SDL_BIG_ENDIAN 
    const Uint32 rshift = 24, gshift = 16, bshift = 8, ashift = 0; 
#else 
    const Uint32 rshift = 0, gshift = 8, bshift = 16, ashift = 24; 
#endif 
    const Uint32 
        rmask = 0xff << rshift, 
        gmask = 0xff << gshift, 
        bmask = 0xff << bshift, 
        amask = 0xff << ashift; 
    Uint32 *ptr; 
    Uint32 kuva_flags; 
    Uint32 kuva_colorkey; 
    Uint8 kuva_alpha; 
    SDL_Rect r1, r2; 
     
    /* Tarkistetaan kuva. */ 
    if (!kuva || !kuva->w || !kuva->h) { 
        return -1; 
    } 
    /* OpenGL:ää varten sivun pitää olla kahden potenssi. */ 
    if (kuva->w > 1 && (kuva->w & (kuva->w - 1))) { 
        return -1; 
    } 
    if (kuva->h > 1 && (kuva->h & (kuva->h - 1))) { 
        return -1; 
    } 
     
    /* Otetaan talteen arvot, jotka muuttuvat funktion aikana */ 
    kuva_flags = kuva->flags; 
    kuva_alpha = kuva->format->alpha; 
    kuva_colorkey = kuva->format->colorkey; 
     
    /* Luodaan apupinta halutussa formaatissa (RGBA). */ 
    apu = SDL_CreateRGBSurface(SDL_SWSURFACE, kuva->w, kuva->h, 32, rmask, gmask, bmask, amask); 
    if (!apu) { 
        return -1; 
    } 
    SDL_FillRect(apu, 0, 0); 
     
    /* Poistetaan erityiset läpinäkyvyysasetukset. */ 
    SDL_SetAlpha(kuva, 0, 0); 
    if ((kuva_flags & SDL_SRCALPHA) != 0 && kuva->format->Amask) { 
        SDL_SetColorKey(kuva, 0, 0); 
    } 
     
    /* OpenGL:n ja SDL:n y-akselit osoittavat eri suuntiin. 
     * Kopioidaan siis kuva pikselirivi kerrallaan ylösalaisin. */ 
    r1.x = r2.x = 0; 
    r1.h = r2.h = 1; 
    r1.w = r2.w = kuva->w; 
    for (r1.y = 0, r2.y = kuva->h - 1; r2.y >= 0; ++r1.y, --r2.y) { 
        SDL_BlitSurface(kuva, &r1, apu, &r2); 
    } 
     
    /* Koko pinnan alfa-arvo pitää palauttaa erikseen, jos sellainen on. */ 
    if ((kuva_flags & SDL_SRCALPHA) && !kuva->format->Amask && kuva_alpha != 0xff) { 
        for (r1.y = 0; r1.y < apu->h; ++r1.y) { 
            ptr = (Uint32*)((Uint8*) apu->pixels + r1.y * apu->pitch); 
            for (r1.x = 0; r1.x < apu->w; ++r1.x) { 
                if ((ptr[r1.x] & amask) != 0) { 
                    ptr[r1.x] &= (kuva_alpha << ashift) | ~amask; 
                } 
            } 
        } 
    } 
     
    /* Lähetetään kuva OpenGL:lle, tuhotaan apupinta ja palautetaan asetukset. */ 
    glTexImage2D(GL_TEXTURE_2D, 0, 4, apu->w, apu->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, apu->pixels); 
    SDL_FreeSurface(apu); 
    SDL_SetAlpha(kuva, kuva_flags, kuva_alpha); 
    SDL_SetColorKey(kuva, kuva_flags, kuva_colorkey); 
    return 0;
}
