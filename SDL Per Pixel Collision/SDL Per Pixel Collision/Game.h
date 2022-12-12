#ifndef GAME_H
#define GAME_H

#include "Entity.h"

class Game
{
	public:
		Game();
		~Game();

		void OnExecute();

		void OnThink();
		void OnUpdate();
		void OnRender();

	private:
		int ScreenWidth;
		int ScreenHeight;
		int ScreenBPP;
		Uint32 ScreenFlags;
		
		bool done;

		double thisTime;
		double lastTime;
		double deltaTime;

		SDL_Surface* screen;
		SDL_Event event;

		Entity* ship;
		Entity* asteroid;
};

#endif