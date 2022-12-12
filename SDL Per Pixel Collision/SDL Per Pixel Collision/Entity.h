#ifndef ENTITY_H
#define ENTITY_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

struct Vector
{
	float X;
	float Y;

	Vector()
	{
		X = 0.0f;
		Y = 0.0f;
	}
};

class Entity
{
	public:
		Entity(char* filename, int tilesX, int tilesY, double frameRate);
		~Entity();

	public:
		Vector position;
		Vector origin;

	public:
		SDL_Surface* surface;

		int tilesX;
		int tilesY;
		int tileWidth;
		int tileHeight;
		
		int frame;
		int frameCount;
		
		double frameInterval;
		double frameTimeRemaining;

	public:		
		void Update(double deltaTime);
		void Render(SDL_Surface* screen);

	public:	
		SDL_Rect GetBounds();
		SDL_Rect GetFrameBounds();
		SDL_Rect NormalizeBounds(const SDL_Rect& rect);

		static SDL_Rect Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB);
		static bool CheckCollision(Entity* entityA, Entity* entityB);
		static bool GetAlphaXY(Entity* entity, int x, int y);
};

#endif