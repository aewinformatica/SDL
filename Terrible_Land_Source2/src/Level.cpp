// Level.cpp

#include "../include/Level.h"

// No-arg Constructor.  Added so that this is a legal class.
Level::Level() {

	startX = 0;
	endX = 1000;
	currentX = startX;
}

// Constructor for single screen
Level::Level(	int inStartX,
				int inEndX,
				SDL_Surface * inScreen1 ) {

	startX = inStartX;
	endX = inEndX;
	currentX = startX;
	screen1 = inScreen1;
	singleScreen = true;

	scrollScreenRight = false;
	scrollScreenLeft = false;
	currentGameGroundLevel = GROUND_LEVEL;

	gotHit = Mix_LoadWAV("Sound/FX/got_hit.wav");
	ouch = Mix_LoadWAV("Sound/FX/ouch.wav");
	tristanOof = Mix_LoadWAV("Sound/FX/tristan_oof.wav");
	
	playerName = PATRICK;
}

// Constructor for splitscreen
Level::Level(	int inStartX,
				int inEndX,
				SDL_Surface * inScreen1,
				SDL_Surface * inScreen2 ) {

	startX = inStartX;
	endX = inEndX;
	currentX = startX;
	screen1 = inScreen1;
	screen2 = inScreen2;
	singleScreen = false;

	scrollScreenRight = false;
	scrollScreenLeft = false;
	currentGameGroundLevel = GROUND_LEVEL;
}

// Helper function.  Copies attributes of one Level over to those of this one.
void Level::copy(const Level & t) {

	// copy all attributes

}

// Helper function to free all space dynamically allocated for Level
void Level::deallocate() {

	for (int i = 0; i < NUM_Z_LEVELS; i++) {
		(allZ[i]).clear();
	}
	
	Mix_FreeChunk(gotHit);
	Mix_FreeChunk(ouch);
	Mix_FreeChunk(tristanOof);
}

// Copy constructor.  Necessarily overridden because construction involves
// dynamic allocation.  Should not need to be used during the lab, but is
// included for completeness.
Level::Level(const Level & t) { copy(t); }

// Destructor.  Overridden because of the dynamic allocation done during
// construction.  Should not be explicitly called during the program, but
// is necessary anyway.
Level::~Level() {

	deallocate();

}

// Assignment operator overload.  Necessary due to dynamic allocation.
// Should not be needed during this lab, but is included for completeness.
Level & Level::operator=(const Level & t) {

	// Deallocate space already used by the current object.
	deallocate();

	// Now copy as if this were a brand new Level object.
	copy(t);

	// Return reference to this object for cascading.
	return *this;

}

// For advancing to new level
void Level::emptyAll() {
	deallocate();
}

// Detect Collisions between Entities in given location
void Level::handleCollisions(	Player * player ) {

	int j;
	if (player->getGroundLevel() < currentGameGroundLevel) {
		player->setGroundLevel(currentGameGroundLevel);
		player->setOnLedge(false);
		player->setFalling(true);
	}

	for (int i = 0; i < NUM_Z_LEVELS; i++) {
		switch (i) {

			case Z_LEVEL_SKY : 
						break;

			case Z_LEVEL_TREES :
						
						// If player is falling
						if (player->getYSpeed() < 0 ) {
							for (j = 0; j < (int)allZ[i].size(); j++) {
								Tree * tree = static_cast<Tree*>(allZ[i][j]);
								
								// if the player is over top of a tree
								if (	player->getX() + player->getWidth() - 50 > tree->getX()
									&&	player->getX() + 60 < tree->getX() + tree->getWidth()
									) {
										// and he's right on top of the tree.
										if 	( player->getY() + player->getHeight() == tree->getY() ) {
												player->setGroundLevel(tree->getY() );								
										}
										// (or somewhere just past it.)
										else if ( player->getY() + player->getHeight() > tree->getY() 
											&& player->getY() + player->getHeight() > tree->getY()+ player->getYSpeed() )
										{
											player->setGroundLevel(tree->getY() );
											player->setY(tree->getY() - player->getHeight());
										}
								}
							}
						}
						break;

			case Z_LEVEL_BAD_GUYS :
						for (j = 0; j < (int)allZ[i].size(); j++) {
							BadGuy * badGuy = static_cast<BadGuy*>(allZ[i][j]);

							if (	!player->getInvincibleAfterBeingHit()
								&&	fabs(player->getY() - badGuy->getY() ) < player->getHeight()
								&&	player->getX() + player->getWidth() > badGuy->getX()
								&&	player->getX() < badGuy->getX() + badGuy->getWidth()
								) {
								switch (player->getName() ) {

									case (PATRICK):	
											Mix_PlayChannel(3,ouch,0);
											break;

									case (TRISTAN):	
											Mix_PlayChannel(3,tristanOof,0);
											break;

								}
								
								player->changeLife(-10);
								player->setInvincibleAfterBeingHit();
							}
						}
						break;

			case Z_LEVEL_BAD_GUY_BOSS :
						for (j = 0; j < (int)allZ[i].size(); j++) {
							BadGuyBoss * badGuyBoss = static_cast<BadGuyBoss*>(allZ[i][j]);

							if (	!player->getInvincibleAfterBeingHit()
								&&	fabs(player->getY() - badGuyBoss->getY() ) < player->getHeight()
								&&	player->getX() + player->getWidth() > badGuyBoss->getX()
								&&	player->getX() < badGuyBoss->getX() + badGuyBoss->getWidth()
								) {
								switch (player->getName() ) {

									case (PATRICK):	
											Mix_PlayChannel(3,ouch,0);
											break;

									case (TRISTAN):	
											Mix_PlayChannel(3,tristanOof,0);
											break;

								}
								player->changeLife(-35);
								player->setInvincibleAfterBeingHit();
							}
						}
						break;

			case Z_LEVEL_FLYING_BAD_GUYS :
						for (j = 0; j < (int)allZ[i].size(); j++) {
							FlyingBadGuy * flyingBadGuy = static_cast<FlyingBadGuy*>(allZ[i][j]);

							if (	!player->getInvincibleAfterBeingHit()
								&&	(		(player->getY() - flyingBadGuy->getY() < flyingBadGuy->getHeight() && player->getY() - flyingBadGuy->getY() > 0
										||	flyingBadGuy->getY() - player->getY() < player->getHeight() && player->getY() - flyingBadGuy->getY() < 0)  )
								&&	player->getX() + player->getWidth() > flyingBadGuy->getX()
								&&	player->getX() < flyingBadGuy->getX() + flyingBadGuy->getWidth()
								) {
								switch (player->getName() ) {

									case (PATRICK):	
											Mix_PlayChannel(3,ouch,0);
											break;

									case (TRISTAN):	
											Mix_PlayChannel(3,tristanOof,0);
											break;

								}
								player->changeLife(-15);
								player->setInvincibleAfterBeingHit();
							}
						}
						break;

			case Z_LEVEL_WEAPONS :
						for (j = 0; j < (int)allZ[i].size(); j++) {
							CandyCane * candyCane = static_cast<CandyCane*>(allZ[i][j]);
							if (	!player->getHasCandyCane()
								&&	!candyCane->getCandyCaneThrown()
								&&	fabs(player->getY() - candyCane->getY() ) < player->getHeight()
								&&	player->getX() + player->getWidth() > candyCane->getX()
								&&	player->getX() < candyCane->getX() + candyCane->getWidth()
								) {
								player->pickUpCandyCane(candyCane);
							}

							for (j = 0; j < (int)allZ[Z_LEVEL_BAD_GUYS].size(); j++) {
								BadGuy * badGuy = static_cast<BadGuy*>(allZ[Z_LEVEL_BAD_GUYS][j]);

								if (	candyCane->getDeadly()
									&&	fabs(badGuy->getY() - candyCane->getY() ) < badGuy->getHeight()
									&&	badGuy->getX() + badGuy->getWidth() > candyCane->getX()
									&&	badGuy->getX() < candyCane->getX() + candyCane->getWidth()
									) {

									Mix_PlayChannel(2,gotHit,0);
									badGuy->setGroundLevel(SCREEN_HEIGHT + badGuy->getHeight() + 50);
									badGuy->setDead(true);
									candyCane->setCandyCaneThrown(false);
									candyCane->setReturnToPlayer(true);
								}
							}

							for (j = 0; j < (int)allZ[Z_LEVEL_BAD_GUY_BOSS].size(); j++) {
								BadGuyBoss * badGuyBoss = static_cast<BadGuyBoss*>(allZ[Z_LEVEL_BAD_GUY_BOSS][j]);

								if (	candyCane->getDeadly()
									&&	fabs(badGuyBoss->getY() - candyCane->getY() ) < badGuyBoss->getHeight()
									&&	badGuyBoss->getX() + badGuyBoss->getWidth() > candyCane->getX()
									&&	badGuyBoss->getX() < candyCane->getX() + candyCane->getWidth()
									) {

									Mix_PlayChannel(2,gotHit,0);
									badGuyBoss->changeLife(-35);
									if (badGuyBoss->getLife() < 1) {
										badGuyBoss->setGroundLevel(SCREEN_HEIGHT + badGuyBoss->getHeight() + 50);
										badGuyBoss->setDead(true);
									}
									candyCane->setCandyCaneThrown(false);
									candyCane->setReturnToPlayer(true);
								}
							}

							for (j = 0; j < (int)allZ[Z_LEVEL_FLYING_BAD_GUYS].size(); j++) {
								FlyingBadGuy * flyingBadGuy = static_cast<FlyingBadGuy*>(allZ[Z_LEVEL_FLYING_BAD_GUYS][j]);

								if (	candyCane->getDeadly()
									&&	fabs(flyingBadGuy->getY() - candyCane->getY() ) < flyingBadGuy->getHeight()
									&&	flyingBadGuy->getX() + flyingBadGuy->getWidth() > candyCane->getX()
									&&	flyingBadGuy->getX() < candyCane->getX() + candyCane->getWidth()
									) {

									Mix_PlayChannel(2,gotHit,0);
									flyingBadGuy->setGroundLevel(SCREEN_HEIGHT + flyingBadGuy->getHeight() + 50);
									flyingBadGuy->setDead(true);
									candyCane->setCandyCaneThrown(false);
									candyCane->setReturnToPlayer(true);
								}
							}

							if (	candyCane->getX() < 0
								||	candyCane->getX() + candyCane->getWidth() > SCREEN_WIDTH ) {
								candyCane->setCandyCaneThrown(false);
								candyCane->setReturnToPlayer(true);
							}
						}
						break;

			case Z_LEVEL_GROUND :
						for (j = 0; j < (int)allZ[i].size(); j++) {
							//loop
						}
						break;

			case Z_LEVEL_LEDGES :
				for (j = 0; j < (int)allZ[i].size(); j++) {
					Ledge * ledge = static_cast<Ledge*>(allZ[i][j]);

					if (player->getFalling() ) {
						if (	player->getX() + player->getWidth() > ledge->getX()
							&&	player->getX() < ledge->getX() + ledge->getWidth()
							) {	
								if (player->getY() + player->getHeight() == ledge->getY() ) {
									player->setGroundLevel(ledge->getY() );
									if (!ledge->getMoving() ) {
										ledge->setMoving(true);										
									}	
									player->setOnLedge(true);
								}
								else if ( player->getY() + player->getHeight() > ledge->getY() 
									&& player->getY() + player->getHeight() > ledge->getY()+ player->getYSpeed() )
								{
									player->setY(ledge->getY() - player->getHeight());
									player->setGroundLevel(ledge->getY() );
									if (!ledge->getMoving() ) {
										ledge->setMoving(true);										
									}
									player->setOnLedge(true);
								}
						}
					}
				}
				break;
		}
	}
}

// Getters
int Level::getStartX() { return startX; }
int Level::getEndX() { return endX; }
int Level::getCurrentX() { return currentX; }
bool Level::getScrollScreenRight() { return scrollScreenRight; }
bool Level::getScrollScreenLeft() { return scrollScreenLeft; }
int Level::getCurrentGameGroundLevel() { return currentGameGroundLevel; }

// Setters
void Level::setStartX(int inStartX) { startX = inStartX; }
void Level::setEndX(int inEndX) { endX = inEndX; }
void Level::setCurrentX(int inCurrentX) { currentX = inCurrentX; }
void Level::setScrollScreenRight(bool inScrollScreenRight) { scrollScreenRight = inScrollScreenRight; }
void Level::setScrollScreenLeft(bool inScrollScreenLeft) { scrollScreenLeft = inScrollScreenLeft; }
void Level::setCurrentGameGroundLevel(int inCurrentGameGroundLevel) { currentGameGroundLevel = inCurrentGameGroundLevel; }
void Level::changeCurrentX(int changeCurrentX) {
	currentX += changeCurrentX;
}

// Add an entity
void Level::addEntity(	Entity * inEntity,
						int zCoord ) {

	allZ[zCoord].push_back( inEntity );
}

// Remove an entity
void Level::removeEntity(	Entity * inEntity ) {

	for (int i = 0; i < NUM_Z_LEVELS; i++) {
		for (int j = 0; j < (int)allZ[i].size(); j++) {
			if (allZ[i][j] == inEntity)
				allZ[i].erase( allZ[i].begin() + j );
		}
	}
}

void Level::checkForScrollScreen(Player * player) {

	// Check for scrollScreenLeft
	if (	player->getX() < SCROLL_LENGTH
		&&	currentX > startX )
	{
		scrollScreenLeft = true;
		changeCurrentX( player->getMoveSpeed() );
	} else if (scrollScreenLeft) {
		scrollScreenLeft = false;
	}

	// Check for scrollScreenRight
	if (	(SCREEN_WIDTH - player->getX() < SCROLL_LENGTH + player->getWidth()
		&&	currentX < endX
		) )
	{
		scrollScreenRight = true;
		changeCurrentX( player->getMoveSpeed() );
	} else if (scrollScreenRight) {
		scrollScreenRight = false;
	}
}

void Level::loadLevel(int levelNumber) {

	char buffer[1];
	string fileName = "Levels/level_";
	fileName += itoa(levelNumber, buffer, 10);
	fileName += ".txt";

	int zLevel;
	int treeNum, badGuyNum, ledgeNum, candyCaneNum, flyingBadGuyNum, badGuyBossNum; // because intializations are skipped by case
	int numEntitiesPerLevel[NUM_Z_LEVELS];

	ifstream levelFile( fileName.c_str(), ios::in );
	if ( !levelFile ) {
		cerr << "File could not be opened" << endl;
	}

	if (singleScreen) {
		for (int i = 0; i < NUM_Z_LEVELS; i++) {
			levelFile >> zLevel;
			levelFile >> numEntitiesPerLevel[zLevel];
			if (numEntitiesPerLevel[zLevel] == 0 && zLevel == Z_LEVEL_SIGNS) continue;

				switch (zLevel) {

					case Z_LEVEL_SKY : 
								Tile * skyTile;
								char skyTileName [256];
								levelFile >> skyTileName;
								skyTile = new Tile(	0, 
													SCREEN_WIDTH,
													0,
													GROUND_LEVEL,
													30,
													405,
													skyTileName,
													screen1 );

								addEntity(skyTile, Z_LEVEL_SKY);
								break;

					case Z_LEVEL_TREES :
								Tree * tree;
								int treeX;
								char treeFileName[256];
								levelFile >> treeFileName;
								for (treeNum = 0; treeNum < numEntitiesPerLevel[Z_LEVEL_TREES]; treeNum++) {
									levelFile >> treeX;
									tree = new Tree(	treeX, 
														currentGameGroundLevel - TREE_HEIGHT - 1, // the  -1 is to make the player not skip the tree for collisions
														204, 
														189,
														treeFileName,
														screen1 );

									addEntity(tree, Z_LEVEL_TREES);
								}
								break;

					case Z_LEVEL_BAD_GUYS :
								BadGuy * badGuy;
								int badGuyX;
								for (badGuyNum = 0; badGuyNum < numEntitiesPerLevel[Z_LEVEL_BAD_GUYS]; badGuyNum++) {
									levelFile >> badGuyX;
									badGuy = new BadGuy(	badGuyX, 
															currentGameGroundLevel - BAD_GUY_HEIGHT,
															BAD_GUY_WIDTH, 
															BAD_GUY_HEIGHT,
															currentGameGroundLevel,
															screen1 );

									addEntity(badGuy, Z_LEVEL_BAD_GUYS);
								}
								break;

					case Z_LEVEL_BAD_GUY_BOSS :
								BadGuyBoss * badGuyBoss;
								int badGuyBossX;
								for (badGuyBossNum = 0; badGuyBossNum < numEntitiesPerLevel[Z_LEVEL_BAD_GUY_BOSS]; badGuyBossNum++) {
									levelFile >> badGuyBossX;
									badGuyBoss = new BadGuyBoss(	badGuyBossX, 
																	currentGameGroundLevel - BAD_GUY_BOSS_HEIGHT,
																	BAD_GUY_BOSS_WIDTH, 
																	BAD_GUY_BOSS_HEIGHT,
																	currentGameGroundLevel,
																	screen1 );

									addEntity(badGuyBoss, Z_LEVEL_BAD_GUY_BOSS);
								}
								break;

					case Z_LEVEL_FLYING_BAD_GUYS :
								BadGuy * flyingBadGuy;
								int flyingBadGuyX;
								for (flyingBadGuyNum = 0; flyingBadGuyNum < numEntitiesPerLevel[Z_LEVEL_FLYING_BAD_GUYS]; flyingBadGuyNum++) {
									levelFile >> flyingBadGuyX;
									flyingBadGuy = new FlyingBadGuy(	flyingBadGuyX, 
																		25,
																		FLYING_BAD_GUY_WIDTH, 
																		FLYING_BAD_GUY_HEIGHT,
																		currentGameGroundLevel,
																		screen1 );

									addEntity(flyingBadGuy, Z_LEVEL_FLYING_BAD_GUYS);
								}
								break;

					case Z_LEVEL_WEAPONS :
								CandyCane * candyCane;
								int candyCaneX;
								for (candyCaneNum = 0; candyCaneNum < numEntitiesPerLevel[Z_LEVEL_WEAPONS]; candyCaneNum++) {
									levelFile >> candyCaneX;
									candyCane = new CandyCane(	candyCaneX, 
																currentGameGroundLevel - CANDY_CANE_HEIGHT,
																CANDY_CANE_WIDTH, 
																CANDY_CANE_HEIGHT,
																screen1 );

									addEntity(candyCane, Z_LEVEL_WEAPONS);
								}
								break;

					case Z_LEVEL_GROUND : 
								Tile * groundTile;
								char groundTileName [256];
								levelFile >> groundTileName;
								groundTile = new Tile(	0, 
														SCREEN_WIDTH,
														GROUND_LEVEL, 
														SCREEN_HEIGHT,
														106,
														106,
														groundTileName,
														screen1 );

								addEntity(groundTile, Z_LEVEL_GROUND);
								break;

					case Z_LEVEL_LEDGES : 
								Ledge * ledge;
								int ledgeX, ledgeY;
								for (ledgeNum = 0; ledgeNum < numEntitiesPerLevel[Z_LEVEL_LEDGES]; ledgeNum++) {
									levelFile >> ledgeX >> ledgeY;
									ledge = new Ledge(	ledgeX, 
														currentGameGroundLevel - ledgeY,
														175, 
														46,
														"images/ledge.bmp",
														screen1,
														false );

									addEntity(ledge, Z_LEVEL_LEDGES);
								}
								break;

					case Z_LEVEL_SIGNS :
								Entity * entity;
								entity = new Entity(	startX + 250,
														currentGameGroundLevel - 200,
														100, 
														200,
														"images/sign_start.bmp",
														screen1 );
								addEntity(entity, Z_LEVEL_SIGNS);

								entity = new Entity(	endX + 200,
														currentGameGroundLevel - 200,
														100, 
														200,
														"images/sign_finish.bmp",
														screen1 );
								addEntity(entity, Z_LEVEL_SIGNS);
								break;
				}
		}

	} else {
		for (int i = 0; i < NUM_Z_LEVELS; i++) {
			levelFile >> zLevel;
			levelFile >> numEntitiesPerLevel[i];

				switch (zLevel) {

					case Z_LEVEL_SKY : 
								Tile * skyTile;
								char skyTileName [256];
								levelFile >> skyTileName;
								skyTile = new Tile(	0, 
													SCREEN_WIDTH,
													0,
													GROUND_LEVEL,
													30,
													405,
													skyTileName,
													screen1,
													screen2 );

								addEntity(skyTile, Z_LEVEL_SKY);
								break;

					case Z_LEVEL_TREES :
								Tree * tree;
								int treeX;
								for (treeNum = 0; treeNum < numEntitiesPerLevel[Z_LEVEL_TREES]; treeNum++) {
									levelFile >> treeX;
									tree = new Tree(	treeX, 
														currentGameGroundLevel - TREE_HEIGHT - 1, // the  -1 is to make the player not skip the tree for collisions
														204, 
														189,
														"images/tree.bmp",
														screen1,
														screen2 );

									addEntity(tree, Z_LEVEL_TREES);
								}
								break;

					case Z_LEVEL_BAD_GUYS :
								BadGuy * badGuy;
								int badGuyX;
								for (badGuyNum = 0; badGuyNum < numEntitiesPerLevel[Z_LEVEL_BAD_GUYS]; badGuyNum++) {
									levelFile >> badGuyX;
									badGuy = new BadGuy(	badGuyX, 
															currentGameGroundLevel - BAD_GUY_HEIGHT,
															BAD_GUY_WIDTH, 
															BAD_GUY_HEIGHT,
															currentGameGroundLevel,
															screen1,
															screen2 );

									addEntity(badGuy, Z_LEVEL_BAD_GUYS);
								}
								break;

					case Z_LEVEL_WEAPONS :
								break;

					case Z_LEVEL_GROUND : 
								Tile * groundTile;
								char groundTileName [256];
								levelFile >> groundTileName;
								groundTile = new Tile(	0, 
														SCREEN_WIDTH,
														GROUND_LEVEL, 
														SCREEN_HEIGHT,
														106,
														106,
														groundTileName,
														screen1,
														screen2 );

								addEntity(groundTile, Z_LEVEL_GROUND);
								break;

					case Z_LEVEL_LEDGES : 
								Ledge * ledge;
								int ledgeX, ledgeY;
								for (ledgeNum = 0; ledgeNum < numEntitiesPerLevel[Z_LEVEL_LEDGES]; ledgeNum++) {
									levelFile >> ledgeX >> ledgeY;
									ledge = new Ledge(	ledgeX, 
														currentGameGroundLevel - ledgeY,
														175, 
														46,
														"images/ledge.bmp",
														screen1,
														screen2,
														false );

									addEntity(ledge, Z_LEVEL_LEDGES);
								}
								break;
				}
		}
	}
}

void Level::update(Player * player) {

	checkForScrollScreen(player);

	int moveSpeed = -player->getMoveSpeed();

	int scrollValue = 0;

	if (scrollScreenLeft) {
		scrollValue = 1;
	} else if (scrollScreenRight) {
		scrollValue = -1;
	}

	int j;

	if (scrollValue != 0) {

		for (int i = 0; i < NUM_Z_LEVELS; i++) {
			
			switch (i) {

				case Z_LEVEL_SKY : 
							break;

				case Z_LEVEL_TREES :
							Tree * tree;
							for (j = 0; j < (int)allZ[i].size(); j++) {

								tree = static_cast<Tree*>(allZ[i][j]);
								tree->changeX( moveSpeed );
							}
							break;

				case Z_LEVEL_BAD_GUYS :
							BadGuy * badGuy;
							for (j = 0; j < (int)allZ[i].size(); j++) {

								badGuy = static_cast<BadGuy*>(allZ[i][j]);
								badGuy->changeX( moveSpeed );
							}
							break;

				case Z_LEVEL_BAD_GUY_BOSS :
							BadGuyBoss * badGuyBoss;
							for (j = 0; j < (int)allZ[i].size(); j++) {

								badGuyBoss = static_cast<BadGuyBoss*>(allZ[i][j]);
								badGuyBoss->changeX( moveSpeed );
							}
							break;

				case Z_LEVEL_FLYING_BAD_GUYS :
							FlyingBadGuy * flyingBadGuy;
							for (j = 0; j < (int)allZ[i].size(); j++) {

								flyingBadGuy = static_cast<FlyingBadGuy*>(allZ[i][j]);
								flyingBadGuy->changeX( moveSpeed );
							}
							break;

				case Z_LEVEL_WEAPONS :

							CandyCane * candyCane;

							for (j = 0; j < (int)allZ[i].size(); j++) {

								candyCane = static_cast<CandyCane*>(allZ[i][j]);

								if (!candyCane->getAttachedToPlayer() ) {
									candyCane->changeX( moveSpeed );
								}
							}
							break;

				case Z_LEVEL_GROUND :
							for (j = 0; j < (int)allZ[i].size(); j++) {
								allZ[i][j]->changeX( moveSpeed );
							}
							break;

				case Z_LEVEL_LEDGES :

							Ledge * ledge;

							for (j = 0; j < (int)allZ[i].size(); j++) {

								ledge = static_cast<Ledge*>(allZ[i][j]);

								ledge->changeX( moveSpeed );
							}

							break;

				case Z_LEVEL_SIGNS :
							for (j = 0; j < (int)allZ[i].size(); j++) {
								allZ[i][j]->changeX( moveSpeed );
							}
							break;
			}
		}
	}

	for (int i = 0; i < NUM_Z_LEVELS; i++) {
		
		switch (i) {

			case Z_LEVEL_SKY : 
						break;

			case Z_LEVEL_TREES :
						break;

			case Z_LEVEL_BAD_GUYS :
			case Z_LEVEL_BAD_GUY_BOSS :

						BadGuy * badGuy;

						for (j = 0; j < (int)allZ[i].size(); j++) {

							badGuy = static_cast<BadGuy*>(allZ[i][j]);

							badGuy->update(player);

							// NOT DYNAMIC FOR SOME REASON!!!!
							if (badGuy->getX() > endX) {
								removeEntity(badGuy);
								//writeErrorToFile("badGuy was nixed for going beyond level");
							}
						}
						break;

			case Z_LEVEL_FLYING_BAD_GUYS :

						FlyingBadGuy * flyingBadGuy;

						for (j = 0; j < (int)allZ[i].size(); j++) {

							flyingBadGuy = static_cast<FlyingBadGuy*>(allZ[i][j]);

							flyingBadGuy->update(player);

							// NOT DYNAMIC FOR SOME REASON!!!!
							if (flyingBadGuy->getX() > endX) {
								removeEntity(flyingBadGuy);
								//writeErrorToFile("badGuy was nixed for going beyond level");
							}
						}
						break;

			case Z_LEVEL_WEAPONS :

							CandyCane * candyCane;

							for (j = 0; j < (int)allZ[i].size(); j++) {

								candyCane = static_cast<CandyCane*>(allZ[i][j]);

								candyCane->update(player->getX(), player->getY() );

							}

						break;

			case Z_LEVEL_GROUND :
						break;

			case Z_LEVEL_LEDGES :

						Ledge * ledge;

						for (j = 0; j < (int)allZ[i].size(); j++) {

							ledge = static_cast<Ledge*>(allZ[i][j]);

							if (ledge->getMoving() ) {
								ledge->changeX( MOVE_SPEED/20 );
							}
							// NOT DYNAMIC FOR SOME REASON!!!!
							if (ledge->getX() > endX) {
								removeEntity(ledge);
								//writeErrorToFile("ledge was nixed for going beyond level");
							}
						}

						break;
		}
	}
}

void Level::display(Player * player) {

	Entity * entity;

	for (int i = 0; i < NUM_Z_LEVELS; i++) {
		for (int j = 0; j < (int)allZ[i].size(); j++) {
			entity = allZ[i][j];

			if (	i == Z_LEVEL_GROUND
				||	i == Z_LEVEL_SKY
				||  i == Z_LEVEL_SIGNS ) {
				if (singleScreen) {
					entity->displaySingleScreen();
				} else {
					entity->displaySplitScreen();
				}

			} else if (i == Z_LEVEL_WEAPONS) {
				if (singleScreen) {
					player->displaySingleScreen();
					entity->displaySingleScreen();
				} else {
					player->displaySplitScreen();
					entity->displaySplitScreen();
				}

			} else if (	(entity->getX() > -entity->getWidth() ) 
				&&	(entity->getX() < SCREEN_WIDTH) ) {
				if (singleScreen) {
					entity->displaySingleScreen();
				} else {
					entity->displaySplitScreen();
				}
			}
		}
	}
}
