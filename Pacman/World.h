#ifndef WORLD_H
#define WORLD_H

#include <list>
#include <map>
#include "Vector2f.h"
#include "Sprite.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class Drawer;
class PathmapTile;
class Dot;
class BigDot;
class Cherry;
class Lives;

class World
{
public:
	World(void);
	~World(void);

	void Init(Drawer* gameDrawer);
	bool InitCherry(Drawer* gameDrawer);

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);
	bool TileIsATunnel(int anX, int anY);

	void LostALife();
	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);
	void ClearCherry();
	int GetDotCount();

	void Update();

	PathmapTile* GetTile(int aFromX, int aFromY);
	void GetPath(int aFromX, int aFromY, int aToX, int aToY, list<PathmapTile*>& aList, int priorX, int priorY, GhostBehavior behavior, GhostType ghostType);

private:
	enum Directions
	{
		NONE = -1,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList, PathmapTile* priorTile, GhostBehavior ghostBehavior, GhostType ghostType);
	bool ListDoesNotContain(PathmapTile* aFromTile,list<PathmapTile*>& aList);

	bool InitPathmap();
	bool InitDots(Drawer* gameDrawer);
	bool InitBigDots(Drawer* gameDrawer);
	bool InitLives(Drawer* gameDrawer);

	list<PathmapTile*> myPathmapTiles;
	list<Dot*> myDots;
	list<BigDot*> myBigDots;
	list<Cherry*> myCherry;
	list<Lives*> myLives;

	Sprite* boardBackground;
};

#endif // WORLD_H