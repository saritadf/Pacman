#ifndef WORLD_H
#define WORLD_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

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

enum Directions
{
	NONE = -1,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class World
{
public:
	World(void);
	~World(void);

	void Init(Drawer* gameDrawer);

	void Draw(Drawer* aDrawer);
	bool TileIsValid(int anX, int anY);
	bool TileIsATunel(int anX, int anY);

	bool HasIntersectedDot(const Vector2f& aPosition);
	bool HasIntersectedBigDot(const Vector2f& aPosition);
	bool HasIntersectedCherry(const Vector2f& aPosition);
	int GetDotCount();

	void Update();

	void GetPath(int aFromX, int aFromY, int aToX, int aToY, list<PathmapTile*>& aList, int priorX, int priorY);

private:
	PathmapTile* GetTile(int aFromX, int aFromY);
	bool Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList, PathmapTile* priorTile);
	bool ListDoesNotContain(PathmapTile* aFromTile,list<PathmapTile*>& aList);

	bool InitPathmap();
	bool InitDots(Drawer* gameDrawer);
	bool InitBigDots(Drawer* gameDrawer);

	list<PathmapTile*> myPathmapTiles;
	list<Dot*> myDots;
	list<BigDot*> myBigDots;
	list<Cherry*> myCherry;

	Sprite* boardBackground;
};

#endif // WORLD_H