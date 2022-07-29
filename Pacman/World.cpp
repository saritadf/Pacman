#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "World.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "PathmapTile.h"
#include "Dot.h"
#include "BigDot.h"
#include "Drawer.h"
#include "Avatar.h"

World::World(void)
{
}

World::~World(void)
{
	while (!myPathmapTiles.empty()) delete myPathmapTiles.front(), myPathmapTiles.pop_front();	
	while (!myBigDots.empty()) delete myBigDots.front(), myBigDots.pop_front();
	while (!myDots.empty()) delete myDots.front(), myDots.pop_front();
	while (!myCherry.empty()) delete myCherry.front(), myCherry.pop_front();
}

void World::Init(Drawer* gameDrawer)
{
	list<string> assetPaths;
	assetPaths.push_back(ASSET_PATH_PLAYFIELD);
	boardBackground = Sprite::Create(assetPaths, gameDrawer, 1024, 768);
	boardBackground->SetFrame(ASSET_PATH_PLAYFIELD);
	InitPathmap();
	InitDots(gameDrawer);
	InitBigDots(gameDrawer);
}

bool World::InitPathmap()
{
	string line;
	ifstream myfile ("map.txt");
	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'), (line[i] == 'b'), (line[i] == '-'));
				myPathmapTiles.push_back(tile);
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitDots(Drawer* gameDrawer)
{
	Sprite* newSprite = NULL;
	list<string> assetPaths;

	string line;
	ifstream myfile ("map.txt");

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '.')
				{
					assetPaths.clear();
					assetPaths.push_back(ASSET_PATH_SMALL_DOT);
					newSprite = Sprite::Create(assetPaths, gameDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
					Dot* dot = new Dot(Vector2f(float(i* TILE_SIZE), float(lineIndex* TILE_SIZE)), newSprite);
					myDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

bool World::InitBigDots(Drawer* gameDrawer)
{
	Sprite* newSprite = NULL;
	list<string> assetPaths;

	string line;
	ifstream myfile ("map.txt");

	if (myfile.is_open())
	{
		int lineIndex = 0;
		while (! myfile.eof() )
		{
			getline (myfile,line);
			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == 'o')
				{
					assetPaths.clear();
					assetPaths.push_back(ASSET_PATH_BIG_DOT);
					newSprite = Sprite::Create(assetPaths, gameDrawer, SPRITE_SIZEX, SPRITE_SIZEY);
					BigDot* dot = new BigDot(Vector2f(i*TILE_SIZE, lineIndex*TILE_SIZE), newSprite);
					myBigDots.push_back(dot);
				}
			}

			lineIndex++;
		}
		myfile.close();
	}

	return true;
}

void World::Draw(Drawer* aDrawer)
{
	boardBackground->Draw(aDrawer, 0, 0);

	for(list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		dot->Draw(aDrawer);
	}

	for(list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		dot->Draw(aDrawer);
	}
}

bool World::TileIsValid(int anX, int anY)
{
	for(list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (anX == tile->myX && anY == tile->myY && !tile->myIsBlockingFlag && !tile->myaIsBoxWallFlag)
			return true;
	}

	return false;
}

bool World::TileIsATunnel(int anX, int anY)
{
	for (list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (anX == tile->myX && anY == tile->myY && tile->myIsTunnelFlag)
			return true;
	}

	return false;
}

int World::GetDotCount()
{
	return myDots.size() + myBigDots.size();
}

bool World::HasIntersectedDot(const Vector2f& aPosition)
{
	for(list<Dot*>::iterator list_iter = myDots.begin(); list_iter != myDots.end(); list_iter++)
	{
		Dot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myDots.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

//SCORE FIND IT
bool World::HasIntersectedBigDot(const Vector2f& aPosition)
{
	for (list<BigDot*>::iterator list_iter = myBigDots.begin(); list_iter != myBigDots.end(); list_iter++)
	{
		BigDot* dot = *list_iter;
		if ((dot->GetPosition() - aPosition).Length() < 5.f)
		{
			myBigDots.remove(dot);
			delete dot;
			return true;
		}
	}

	return false;
}

bool World::HasIntersectedCherry(const Vector2f& aPosition)
{
	return true;
}

PathmapTile* World::GetTile(int aFromX, int aFromY)
{
	for(list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile->myX == aFromX && tile->myY == aFromY)
		{
			return tile;
		}
	}

	return NULL;
}

bool World::ListDoesNotContain(PathmapTile* aFromTile, list<PathmapTile*>& aList)
{
	for(std::list<PathmapTile*>::iterator list_iter = aList.begin(); list_iter != aList.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		if (tile == aFromTile)
		{
			return false;
		}
	}

	return true;
}

//USE IT FOR THE GHOSTS
void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, list<PathmapTile*>& aList, int priorX, int priorY, GhostBehavior ghostBehavior, GhostType ghostType)
{
	PathmapTile* fromTile = GetTile(aFromX, aFromY);
	PathmapTile* toTile = GetTile(aToX, aToY);
	PathmapTile* priorTile = GetTile(priorX, priorY);

	for (list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		tile->myIsVisitedFlag = false;
	}

	Pathfind(fromTile, toTile, aList, priorTile, ghostBehavior, ghostType);
}

bool isInsideTheBox(PathmapTile* tile)
{
	return (tile->myX > MIN_RANGE_TILEX) && (tile->myX < MAX_RANGE_TILEX)
		&& (tile->myY > MIN_RANGE_TILEY) && (tile->myY < MAX_RANGE_TILEY);
}

bool isAValidPosition(PathmapTile* fromTile, const PathmapTile* nextTile, PathmapTile* priorTile, GhostBehavior ghostBehavior)
{
	if (nextTile)
	{
		// The ghost is inside the box
		if (ghostBehavior == Fear || isInsideTheBox(fromTile))
			return (nextTile != priorTile && !nextTile->myIsBlockingFlag);
		else
			return (nextTile != priorTile && !nextTile->myIsBlockingFlag && !nextTile->myaIsBoxWallFlag);
	}
	else
		return false;
}

float distanceBtwTiles(const PathmapTile* fromTile, const PathmapTile* toTile)
{
	const int dx = toTile->myX - fromTile->myX;
	const int dy = toTile->myY - fromTile->myY;

	return sqrt(dx*dx + dy*dy);
}

bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList, PathmapTile* priorTile, GhostBehavior ghostBehavior, GhostType ghostType)
{
	vector <PathmapTile*> directionTiles;
	
	if (aFromTile->myIsTunnelFlag && !priorTile->myIsTunnelFlag)
	{
		PathmapTile* tile;

		// It is going to the right and it is not coming from the Tunnel already
		if (priorTile->myX < aFromTile->myX)
			tile = GetTile(LEFT_TUNNEL_TILEX, aFromTile->myY);
		else
			tile = GetTile(RIGHT_TUNNEL_TILEX, aFromTile->myY);

		aList.push_back(tile);
		return true;
	}

	// Up 
	directionTiles.push_back(GetTile(aFromTile->myX, aFromTile->myY - 1));
	// Left
	directionTiles.push_back(GetTile(aFromTile->myX - 1, aFromTile->myY));
	// Down
	directionTiles.push_back(GetTile(aFromTile->myX, aFromTile->myY + 1));
	// Right
	directionTiles.push_back(GetTile(aFromTile->myX + 1, aFromTile->myY));

	vector <PathmapTile*> neighbors;

	for (int i=0; i < directionTiles.size(); i++)
	{
		PathmapTile* tile = directionTiles[i];

		if (isAValidPosition(aFromTile,tile, priorTile, ghostBehavior))
			neighbors.push_back(tile);
	}

	stable_sort(neighbors.begin(), neighbors.end(), [&](const PathmapTile* lhs, const PathmapTile* rhs){
		return distanceBtwTiles(lhs, aToTile) < distanceBtwTiles(rhs, aToTile);
		});

	aList.push_back(neighbors.at(0));

	return true;
}