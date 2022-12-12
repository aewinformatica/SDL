#include "Entity.h"

#define Maximum(a, b) ((a > b) ? a : b)
#define Minimum(a, b) ((a < b) ? a : b)

/*
int Maximum(int a, int b)
{
	return ((a > b) ? a : b);
}

int Minimum(int a, int b)
{
	return ((a < b) ? a : b);
}
*/

Entity::Entity(char* filename, int tilesX, int tilesY, double frameRate)
{
	this->surface = IMG_Load(filename);

	this->tilesX = tilesX;
	this->tilesY = tilesY;
	this->tileWidth = surface->w / tilesX;
	this->tileHeight = surface->h / tilesY;
	this->frame = 0;
	this->frameCount = tilesX * tilesY;
	this->frameInterval = 1 / frameRate;
	this->frameTimeRemaining = frameInterval;

	this->origin.X = tileWidth / 2.0f;
	this->origin.Y = tileHeight / 2.0f;
}

Entity::~Entity()
{
	SDL_FreeSurface(surface);
}

void Entity::Update(double deltaTime)
{
	frameTimeRemaining -= deltaTime;
	if(frameTimeRemaining < 0)
	{
		frame++;
		frame %= frameCount;
		frameTimeRemaining = frameInterval;
	}
}

void Entity::Render(SDL_Surface* screen)
{
	SDL_Rect location = GetBounds();	
	SDL_Rect clip = GetFrameBounds();
	
    SDL_BlitSurface(surface, &clip, screen, &location);
}

SDL_Rect Entity::GetBounds()
{
	SDL_Rect bounds;
	bounds.x = (Sint16)(position.X - origin.X);
	bounds.y = (Sint16)(position.Y - origin.Y);
	bounds.w = (Sint16)(tileWidth);
	bounds.h = (Sint16)(tileHeight);

	return bounds;
}

SDL_Rect Entity::GetFrameBounds()
{
	SDL_Rect frameBounds;
	frameBounds.x = (Sint16)(frame % tilesX * tileWidth);
	frameBounds.y = (Sint16)(frame / tilesX * tileHeight);
	frameBounds.w = (Sint16)(tileWidth);
	frameBounds.h = (Sint16)(tileHeight);
	
	return frameBounds;
}

SDL_Rect Entity::NormalizeBounds(const SDL_Rect& rect)
{
	SDL_Rect normalized;
	normalized.x = rect.x - (Sint16)position.X + (Sint16)origin.X + GetFrameBounds().x;
	normalized.y = rect.y - (Sint16)position.Y + (Sint16)origin.Y + GetFrameBounds().y;
	normalized.w = rect.w;
	normalized.h = rect.h;
	
	return normalized;
}

SDL_Rect Entity::Intersection(const SDL_Rect& boundsA, const SDL_Rect& boundsB)
{
	int x1 = Maximum(boundsA.x, boundsB.x);
	int y1 = Maximum(boundsA.y, boundsB.y);
	int x2 = Minimum(boundsA.x + boundsA.w, boundsB.x + boundsB.w);
	int y2 = Minimum(boundsA.y + boundsA.h, boundsB.y + boundsB.h);
	
	int width = x2 - x1;
	int height = y2 - y1;
	
	if(width > 0 && height > 0)
	{
		SDL_Rect intersect = {x1, y1, width, height};
		return intersect;
	}
	else
	{
		SDL_Rect intersect = {0, 0, 0, 0};
		return intersect;
	}
}

bool Entity::CheckCollision(Entity* entityA, Entity* entityB)
{
	SDL_Rect collisionRect = Intersection(entityA->GetBounds(), entityB->GetBounds());

	if(collisionRect.w == 0 && collisionRect.h == 0)
		return false;

	SDL_Rect normalA = entityA->NormalizeBounds(collisionRect);
	SDL_Rect normalB = entityB->NormalizeBounds(collisionRect);

	for(int y = 0; y <= collisionRect.h; y++)
		for(int x = 0; x <= collisionRect.w; x++)
			if(GetAlphaXY(entityA, normalA.x + x, normalA.y + y) && GetAlphaXY(entityB, normalB.x + x, normalB.y + y))
				return true;

	return false;
}

bool Entity::GetAlphaXY(Entity* entity, int x, int y)
{
	int bpp = entity->surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)entity->surface->pixels + y * entity->surface->pitch + x * bpp;
	Uint32 pixelColor;
	
	switch(bpp)
	{
		case(1):
			pixelColor = *p;
			break;
		case(2):
			pixelColor = *(Uint16*)p;
			break;
		case(3):
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				pixelColor = p[0] << 16 | p[1] << 8 | p[2];
			else
				pixelColor = p[0] | p[1] << 8 | p[2] << 16;
			break;
		case(4):
			pixelColor = *(Uint32*)p;
			break;
	}
	
	Uint8 red, green, blue, alpha;
	SDL_GetRGBA(pixelColor, entity->surface->format, &red, &green, &blue, &alpha);

	return alpha > 200;
}
