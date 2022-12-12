// Tree.h

#ifndef Tree_H

#define Tree_H

#include "Entity.h"

#define NUM_TREE_ANIMS    2

class Tree : public Entity {

	public:

	/*
	 *       Special Functions.
	 *
	 */

	// Single-screen constructor
	Tree(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1 );

	// Split-screen constructor
	Tree(	int inX,
			int inY, 
			int inWidth, 
			int inHeight,
			char image[],
			SDL_Surface * inScreen1,
			SDL_Surface * inScreen2 );

	protected:
		//Animation * allAnimations[NUM_TREE_ANIMS];

	private:

};

#endif
