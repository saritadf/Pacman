#include "Pacman.h"
#include "Drawer.h"
#include "SDL.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Avatar.h"
#include "World.h"
#include "Ghost.h"
#include "SpriteFont.h"

Pacman* Pacman::Create(Drawer* aDrawer)
{
	Pacman* pacman = new Pacman(aDrawer);

	if (!pacman->Init())
	{
		delete pacman;
		pacman = NULL;
	}

	return pacman;
}

Pacman::Pacman(Drawer* aDrawer)
: myDrawer(aDrawer)
, myTimeToNextUpdate(40.f)
, myTimeToNextGhost(40.f)
, myInitTime(3.f)
, myNextMovement(-1.f,0.f)
, myScore(0)
, myFps(0)
, myLives(3)
, myGhostGhostCounter(0.f)
{
	Sprite* newSprite = NULL;
	list<string> assetPaths;

	// Avatar
	assetPaths.clear();
	assetPaths.push_back(ASSET_PATH_RIGHT_AVATAR);
	assetPaths.push_back(ASSET_PATH_DOWN_AVATAR);
	assetPaths.push_back(ASSET_PATH_LEFT_AVATAR);
	assetPaths.push_back(ASSET_PATH_UP_AVATAR);
	newSprite = Sprite::Create(assetPaths, myDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
	myAvatar = new Avatar(Vector2f(INIT_AVATAR_POSX * TILE_SIZE, INIT_AVATAR_POSY * TILE_SIZE), newSprite);

	// Ghosts

	// Red Ghost - Blinky
	assetPaths.clear();
	assetPaths.push_back(ASSET_PATH_RED_GHOST);
	assetPaths.push_back(ASSET_PATH_GHOST_VULNERABLE);
	assetPaths.push_back(ASSET_PATH_GHOST_DEAD);
	newSprite = Sprite::Create(assetPaths, myDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
	ghosts.push_back(new Ghost(Vector2f(RED_GHOST_POSX * TILE_SIZE, RED_GHOST_POSY * TILE_SIZE), newSprite, GhostBehavior::Intercept, GhostType::Red));
	
	// Pink Ghost - Pinky
	assetPaths.clear();
	assetPaths.push_back(ASSET_PATH_PINK_GHOST);
	assetPaths.push_back(ASSET_PATH_GHOST_VULNERABLE);
	assetPaths.push_back(ASSET_PATH_GHOST_DEAD);
	newSprite = Sprite::Create(assetPaths, myDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
	ghosts.push_back(new Ghost(Vector2f(PINK_GHOST_POSX * TILE_SIZE, PINK_GHOST_POSY * TILE_SIZE), newSprite, GhostBehavior::Intercept, GhostType::Pink));

	// Cyan Ghost - Inky
	assetPaths.clear();
	assetPaths.push_back(ASSET_PATH_CYAN_GHOST);
	assetPaths.push_back(ASSET_PATH_GHOST_VULNERABLE);
	assetPaths.push_back(ASSET_PATH_GHOST_DEAD);
	newSprite = Sprite::Create(assetPaths, myDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
	ghosts.push_back(new Ghost(Vector2f(CYAN_GHOST_POSX * TILE_SIZE, CYAN_GHOST_POSY * TILE_SIZE), newSprite, GhostBehavior::Intercept, GhostType::Cyan));

	// Orange Ghost - Clyde
	assetPaths.clear();
	assetPaths.push_back(ASSET_PATH_ORANGE_GHOST);
	assetPaths.push_back(ASSET_PATH_GHOST_VULNERABLE);
	assetPaths.push_back(ASSET_PATH_GHOST_DEAD);
	newSprite = Sprite::Create(assetPaths, myDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
	ghosts.push_back(new Ghost(Vector2f(ORANGE_GHOST_POSX * TILE_SIZE, ORANGE_GHOST_POSY * TILE_SIZE), newSprite, GhostBehavior::Intercept, GhostType::Orange));

	myWorld = new World();

	gameplayMessage = SpriteFont::Create(FONT_PATH_FREE_MONO, "", WHITE, FONT_SIZE, myDrawer);
	scoreDisplay = SpriteFont::Create(FONT_PATH_FREE_MONO, "", GREEN, FONT_SIZE, myDrawer);
	livesDisplay = SpriteFont::Create(FONT_PATH_FREE_MONO, "", WHITE, FONT_SIZE, myDrawer);
	fpsDisplay = SpriteFont::Create(FONT_PATH_FREE_MONO, "", WHITE, FONT_SIZE, myDrawer);

	UpdateLives(myLives);
	UpdateScore(0);
}

Pacman::~Pacman(void)
{
	delete fpsDisplay;
	fpsDisplay = NULL;

	delete livesDisplay;
	livesDisplay = NULL;

	delete scoreDisplay;
	scoreDisplay = NULL;

	delete gameplayMessage;
	gameplayMessage = NULL;

	delete myWorld;
	myWorld = NULL;

	delete myDrawer;
	myDrawer = NULL;

	delete myAvatar;
	myAvatar = NULL;

	while (!ghosts.empty()) delete ghosts.front(), ghosts.pop_front();
}

bool Pacman::Init()
{
	myWorld->Init(myDrawer);

	return true;
}

bool Pacman::Update(float aTime)
{
	myInitTime -= aTime;
	myTimeToNextUpdate -= aTime;
	myTimeToNextGhost -= aTime;

	// Waiting to Initialize
	if (myInitTime < 0.f)
	{
		if (!UpdateInput())
			return false;

		if (CheckEndGameCondition())
			return true;
		else if (myLives <= 0)
			return true;

		list<Ghost*>::iterator ghostIterator;

		MoveAvatar();
		myAvatar->Update(aTime);
		for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
		{
			// Ghosts delay to get out
			if (myTimeToNextGhost > 0)
			{
				if ((*ghostIterator)->GetGhostType() == Red || (*ghostIterator)->GetGhostType() == Pink)
				{
					(*ghostIterator)->Update(aTime, myWorld, myAvatar);
				}

				if (myTimeToNextGhost < 15 && (*ghostIterator)->GetGhostType() == Orange)
				{
					(*ghostIterator)->Update(aTime, myWorld, myAvatar);
				}
				else if (myTimeToNextGhost < 30 && (*ghostIterator)->GetGhostType() == Cyan)
				{
					(*ghostIterator)->Update(aTime, myWorld, myAvatar);
				}
			}
			else
			{
				if ((*ghostIterator)->GetGhostType() == Red)
				{
					redGhostPos = (*ghostIterator)->GetPosition();
				}
				else if ((*ghostIterator)->GetGhostType() == Cyan)
				{
					(*ghostIterator)->SetRedGhostPosition(redGhostPos);
				}

				(*ghostIterator)->Update(aTime, myWorld, myAvatar);
			}
		}

		if (myWorld->HasIntersectedDot(myAvatar->GetPosition()))
		{
			UpdateScore(10);
			if (CheckEndGameCondition())
				gameplayMessage->SetText("You win!");
		}

		myGhostGhostCounter -= aTime;

		if (myWorld->HasIntersectedBigDot(myAvatar->GetPosition()))
		{
			UpdateScore(20);

			myGhostGhostCounter = 10.f;
			for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
			{
				(*ghostIterator)->myIsVulnerableFlag = true;
			}
		}

		if (myWorld->HasIntersectedCherry(myAvatar->GetPosition()))
		{
			//UpdateScore(100);
		}

		// Vulnerable Mode is over
		if (myGhostGhostCounter <= 0.f)
		{
			for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
				(*ghostIterator)->myIsVulnerableFlag = false;
		}

		// Chase Mode 
		if (myTimeToNextUpdate > 0.f  && myTimeToNextUpdate < 33.f )
		{
			isChaseMode = true;
			
			for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
				(*ghostIterator)->myIsChaseMode = true;

		}
		//Scatter Mode
		if (myTimeToNextUpdate < 0.f)
		{
			isChaseMode = false;
			myTimeToNextUpdate = 40.f;

			for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
				(*ghostIterator)->myIsChaseMode = false;
		}

		for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
		{
			// Ghost and Avatar Intersection
			if (((*ghostIterator)->GetPosition() - myAvatar->GetPosition()).Length() < 16.f)
			{
				// Vulnerable timer is up
				if (myGhostGhostCounter <= 0.f)
				{
					UpdateLives(myLives - 1);

					// Lose one life
					if (myLives > 0)
					{
						myTimeToNextGhost = 40.f;
						myInitTime = WAIT_INIT_TIME;
						myAvatar->Respawn(Vector2f(INIT_AVATAR_POSX * TILE_SIZE, INIT_AVATAR_POSY * TILE_SIZE));
						myAvatar->Initialize();
						int i = 0;
						for (list<Ghost*>::iterator ghostIt = ghosts.begin(); ghostIt != ghosts.end(); ghostIt++)
						{
							(*ghostIt)->Respawn(Vector2f(ghostsPosX[i] * TILE_SIZE, ghostsPosY[i] * TILE_SIZE));
							i++;
						}
						break;
					}
					// Lost
					else
					{
						gameplayMessage->SetText("You lose!");
						break;
					}
				}
				// Still Time
				// If ghosts are vulnerable and not dead yet
				else if ((*ghostIterator)->myIsVulnerableFlag && !(*ghostIterator)->myIsDeadFlag)
				{
					(*ghostIterator)->myIsVulnerableFlag = false;
					UpdateScore(50);
					(*ghostIterator)->myIsDeadFlag = true;
				}
			}
		}
	}
		if (aTime > 0)
			SetFPS((int)(1 / aTime));

	return true;
}

void Pacman::UpdateScore(int scoreGain)
{
	myScore += scoreGain;
	stringstream stream;
	stream << "Score: ";
	stream << myScore;
	scoreDisplay->SetText(stream.str());
}

void Pacman::UpdateLives(int lives)
{
	myLives = lives;
	stringstream stream;
	stream << "Lives: ";
	stream << myLives;
	livesDisplay->SetText(stream.str());
}

void Pacman::SetFPS(int fps)
{
	myFps = fps;
	stringstream stream;
	stream << "FPS: ";
	stream << myFps;
	fpsDisplay->SetText(stream.str());
}

bool Pacman::UpdateInput()
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_UP])
		myNextMovement = Vector2f(0.f, -1.f);
	else if (keystate[SDL_SCANCODE_DOWN])
		myNextMovement = Vector2f(0.f, 1.f);
	else if (keystate[SDL_SCANCODE_RIGHT])
		myNextMovement = Vector2f(1.f, 0.f);
	else if (keystate[SDL_SCANCODE_LEFT])
		myNextMovement = Vector2f(-1.f, 0.f);

	if (keystate[SDL_SCANCODE_ESCAPE])
		return false;

	return true;
}

void Pacman::MoveAvatar()
{
	int nextTileX, nextTileY;

	const int currentTileX = myAvatar->GetCurrentTileX();
	const int currentTileY = myAvatar->GetCurrentTileY();	
	
	const int priorTileX = myAvatar->GetPriorTileX();
	const int priorTileY = myAvatar->GetPriorTileY();

	nextTileY = currentTileY + int(myNextMovement.myY);
	nextTileX = currentTileX + int(myNextMovement.myX);

	Vector2f destination(float(nextTileX * TILE_SIZE), float(nextTileY * TILE_SIZE));
	Vector2f myPosition(float(currentTileX * TILE_SIZE), float(currentTileY * TILE_SIZE));
	Vector2f priorPosition(float(priorTileX * TILE_SIZE), float(priorTileY * TILE_SIZE));

	Vector2f direction = destination - myPosition;
	Vector2f priorDirection = myPosition - priorPosition;

	if (myWorld->TileIsATunnel(currentTileX, currentTileY))
	{
		 // Left  // Right
		if ((direction.myX < 0 && currentTileX == LEFT_TUNNEL_TILEX) || (direction.myX > 0 && currentTileX == RIGHT_TUNNEL_TILEX))
		{
			nextTileX = (currentTileX == LEFT_TUNNEL_TILEX) ? RIGHT_TUNNEL_TILEX : LEFT_TUNNEL_TILEX;
			myAvatar->Respawn(Vector2f(nextTileX * TILE_SIZE, nextTileY * TILE_SIZE));
		}
	}

	if (myAvatar->IsAtDestination())
	{
		if (myWorld->TileIsValid(nextTileX, nextTileY))
		{
			myAvatar->SetNextTile(nextTileX, nextTileY);
		}
		else
		{		// Going Left
				if ((priorDirection.myX < 0) && !(direction.myX < 0))
				{
					if (myWorld->TileIsValid(currentTileX - 1, currentTileY))
						myAvatar->SetNextTile(currentTileX - 1, currentTileY);
					else
						myAvatar->SetNextTile(currentTileX, currentTileY);
				}
				// Going Right
				else if ((priorDirection.myX > 0) && !(direction.myX > 0))
				{
					if (myWorld->TileIsValid(currentTileX + 1, currentTileY))
						myAvatar->SetNextTile(currentTileX + 1, currentTileY);
					else
						myAvatar->SetNextTile(currentTileX, currentTileY);
				}
				// Going Down
				else if ((priorDirection.myY > 0) && !(direction.myY > 0))
				{
					if (myWorld->TileIsValid(currentTileX, currentTileY + 1))
						myAvatar->SetNextTile(currentTileX, currentTileY + 1);
					else
						myAvatar->SetNextTile(currentTileX, currentTileY);
				}
				// Going Up
				else if ((priorDirection.myY < 0) && !(direction.myY < 0))
				{
					if (myWorld->TileIsValid(currentTileX, currentTileY - 1))
						myAvatar->SetNextTile(currentTileX, currentTileY - 1);
					else
						myAvatar->SetNextTile(currentTileX, currentTileY);
				}
				else
				myAvatar->SetNextTile(currentTileX, currentTileY);
		}
	}
}

bool Pacman::CheckEndGameCondition()
{
	return myWorld->GetDotCount() == 0;
}

bool Pacman::Draw()
{
	list<Ghost*>::iterator ghostIterator;
	myWorld->Draw(myDrawer);
	myAvatar->Draw(myDrawer);
	for (ghostIterator = ghosts.begin(); ghostIterator != ghosts.end(); ghostIterator++)
		(*ghostIterator)->Draw(myDrawer);

	scoreDisplay->Draw(myDrawer, SCORE_POSX, SCORE_POSY);
	livesDisplay->Draw(myDrawer, LIVES_POSX, LIVES_POSY);
	fpsDisplay->Draw(myDrawer, FPS_POSX, FPS_POSY);

	if (CheckEndGameCondition() || myLives <= 0)
		gameplayMessage->Draw(myDrawer, 500, 100);

	return true;
}
