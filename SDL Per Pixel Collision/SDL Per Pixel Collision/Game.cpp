#include "Game.h"

Game::Game()
{
	ScreenWidth = 800;
	ScreenHeight = 600;
	ScreenBPP = 32;
	ScreenFlags = SDL_HWSURFACE | SDL_DOUBLEBUF;

    done = false;

    thisTime = 0.0;
	lastTime = 0.0;
	deltaTime = 0.0;

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_WM_SetCaption("SDL Per Pixel Collision", NULL);
	SDL_ShowCursor(0);

    screen = SDL_SetVideoMode(ScreenWidth, ScreenHeight, ScreenBPP, ScreenFlags);

	ship = new Entity("images/ship.png", 4, 3, 10);
	asteroid = new Entity("images/asteroid.png", 5, 6, 30);

    asteroid->position.X = (float)(ScreenWidth / 2);
    asteroid->position.Y = (float)(ScreenHeight / 2);
}

Game::~Game()
{
	delete ship;
	delete asteroid;

	SDL_Quit();
}

void Game::OnExecute()
{
	while(!done)
	{
		OnThink();
		OnUpdate();
		OnRender();
	}
}

void Game::OnThink()
{
	while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
            done = true;
            
		if(event.type == SDL_KEYDOWN)
			if(event.key.keysym.sym == SDLK_ESCAPE)
				done = true;
		    
		if(event.type == SDL_MOUSEMOTION)
		{
			ship->position.X = event.motion.x;
			ship->position.Y = event.motion.y;
		}
    }
}

void Game::OnUpdate()
{
	lastTime = thisTime;
	thisTime = SDL_GetTicks();
	deltaTime = (thisTime - lastTime) / 1000.0;

	ship->Update(deltaTime);
	asteroid->Update(deltaTime);
}

void Game::OnRender()
{
	SDL_FillRect(screen, NULL, 0);

	SDL_Rect collisionRect = Entity::Intersection(ship->GetBounds(), asteroid->GetBounds());
	//SDL_Rect normalize1 = ship->NormalizeBounds(collisionRect);
	//SDL_Rect normalize2 = asteroid->NormalizeBounds(collisionRect);

	//SDL_BlitSurface(ship->surface, &normalize1, screen, NULL);
	//SDL_BlitSurface(asteroid->surface, &normalize2, screen, NULL);

	if(collisionRect.w != 0 && collisionRect.h != 0)
		if(Entity::CheckCollision(ship, asteroid))
			SDL_FillRect(screen, &collisionRect, SDL_MapRGB(screen->format, 255, 0, 0));
		else
			SDL_FillRect(screen, &collisionRect, SDL_MapRGB(screen->format, 0, 255, 0));

	ship->Render(screen);
	asteroid->Render(screen);

	SDL_Flip(screen);
}

int main(int argc, char* args[])
{
	Game game;
	game.OnExecute();

    return 0;
}
