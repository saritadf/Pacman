#ifndef PACMAN_H
#define PACMAN_H

#include "Vector2f.h"
#include <list>
#include <vector>
#include "SDL_image.h"
#include "Constants.h"

using namespace constants;
using namespace std;

struct SDL_Surface;
class Drawer;
class Avatar;
class World;
class Ghost;
class SpriteFont;

class Pacman
{
public:
	static Pacman* Create(Drawer* aDrawer);
	~Pacman(void);

	bool Update(float aTime);
	bool Draw();

private:
	// Font
	const char* FONT_PATH_FREE_MONO = "freefont-ttf\\sfd\\FreeMono.ttf";
	const int FONT_SIZE = 24;
	const SDL_Color WHITE = { 255,255,255,255 };
	const SDL_Color GREEN = { 0,255,0,255 };

	Pacman(Drawer* aDrawer);
	bool Init();
	bool UpdateInput();
	void MoveAvatar();
	bool CheckEndGameCondition();

	void UpdateScore(int scoreGain);
	void UpdateLives(int lives);
	void SetFPS(int fps);

	Drawer* myDrawer;

	float myInitTime;
	float myTimeToNextUpdate;
	float myGhostGhostCounter;

	int myLives;
	int myScore;
	int myFps;
	int mySaveTimer;
	Vector2f redGhostPos;

	const float SCATTER_TIME = 7.f;
	const float TIMER_FOR_SCATTER_CHASE = 27.f;
	const float WAIT_INIT_TIME = 3.f;

	vector<int> ghostsPosX{ RED_GHOST_POSX, PINK_GHOST_POSX, CYAN_GHOST_POSX, ORANGE_GHOST_POSX };
	vector<int> ghostsPosY{ RED_GHOST_POSY, PINK_GHOST_POSY, CYAN_GHOST_POSY, ORANGE_GHOST_POSY };

	Vector2f myNextMovement;
	Vector2f myPriorPosition;

	Avatar* myAvatar;
	list<Ghost*> ghosts;
	World* myWorld;

	SpriteFont* gameplayMessage;
	SpriteFont* scoreDisplay;
	SpriteFont* livesDisplay;
	SpriteFont* fpsDisplay;
};

#endif // PACMAN_H