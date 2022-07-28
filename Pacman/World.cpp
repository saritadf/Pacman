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
				PathmapTile* tile = new PathmapTile(i, lineIndex, (line[i] == 'x'), (line[i] == 'b'));
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

		if (anX == tile->myX && anY == tile->myY && !tile->myIsBlockingFlag)
			return true;
	}

	return false;
}

bool World::TileIsATunel(int anX, int anY)
{
	for (list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;

		if (anX == tile->myX && anY == tile->myY && tile->myIsTunelFlag)
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

////USE IT FOR THE GHOSTS
//void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, list<PathmapTile*>& aList)
//{
//	PathmapTile* fromTile = GetTile(aFromX, aFromY);
//	PathmapTile* toTile = GetTile(aToX, aToY);
//
//	for(list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
//	{
//		PathmapTile* tile = *list_iter;
//		tile->myIsVisitedFlag = false;
//	}
//
//	Pathfind(fromTile, toTile, aList);
//}

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

//bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList)
//{
//	aFromTile->myIsVisitedFlag = true;
//	aList.push_back(aFromTile);
//
//	while (aFromTile != aToTile && !aList.empty())
//	{
//		PathmapTile* tile = aList.back();
//		if (!tile->myIsVisitedFlag)
//		{
//			tile->myIsVisitedFlag = true;
//		}
//		
//		if (aFromTile != aToTile)
//			break;
//
//		list<PathmapTile*> neighborList;
//		PathmapTile* up = GetTile(aFromTile->myX, aFromTile->myY - 1);
//		if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag) //&& ListDoesNotContain(up, aList))
//			neighborList.push_front(up);
//
//		PathmapTile* left = GetTile(aFromTile->myX - 1, aFromTile->myY);
//		if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag) // && ListDoesNotContain(left, aList))
//			neighborList.push_front(left);
//
//		PathmapTile* down = GetTile(aFromTile->myX, aFromTile->myY + 1);
//		if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag) //&& ListDoesNotContain(down, aList))
//			neighborList.push_front(down);
//
//		PathmapTile* right = GetTile(aFromTile->myX + 1, aFromTile->myY);
//		if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag) //&& ListDoesNotContain(right, aList))
//			neighborList.push_front(right);
//
//		for (std::list<PathmapTile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
//		{
//			aFromTile = *list_iter;
//			aList.push_back(tile);
//		}
//
		//if (!neighborList.empty())
		//{
		//	aFromTile = neighborList.front();
		//	aFromTile->myIsVisitedFlag = true;
		//	aList.push_back(aFromTile);
		//}
		//else if (!aList.empty())
		//{
		//	aList.pop_back();
		//	aFromTile = aList.back();
		//}
		//else
		//{
		//	break;
		//}
//	}
//
//	return true;
//}

//USE IT FOR THE GHOSTS
void World::GetPath(int aFromX, int aFromY, int aToX, int aToY, list<PathmapTile*>& aList, int priorX, int priorY)
{
	PathmapTile* fromTile = GetTile(aFromX, aFromY);
	PathmapTile* toTile = GetTile(aToX, aToY);
	PathmapTile* priorTile = GetTile(priorX, priorY);

	for (list<PathmapTile*>::iterator list_iter = myPathmapTiles.begin(); list_iter != myPathmapTiles.end(); list_iter++)
	{
		PathmapTile* tile = *list_iter;
		tile->myIsVisitedFlag = false;
	}

	Pathfind(fromTile, toTile, aList, priorTile);
}

bool isAValidPosition(PathmapTile* tile, PathmapTile* priorTile)
{
	return (tile != priorTile && tile && !tile->myIsBlockingFlag);
}

float distanceBtwTiles(const PathmapTile* fromTile, const PathmapTile* toTile)
{
	const int dx = toTile->myX - fromTile->myX;
	const int dy = toTile->myY - fromTile->myY;

	return sqrt(dx*dx + dy*dy);
}

bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList, PathmapTile* priorTile)
{
	PathmapTile* upTile = GetTile(aFromTile->myX, aFromTile->myY - 1);
	PathmapTile* leftTile = GetTile(aFromTile->myX - 1, aFromTile->myY);
	PathmapTile* downTile = GetTile(aFromTile->myX, aFromTile->myY + 1);
	PathmapTile* rightTile = GetTile(aFromTile->myX + 1, aFromTile->myY);

	vector <PathmapTile*> neightbors;

	if (isAValidPosition(upTile, priorTile))
		neightbors.push_back(upTile);

	if (isAValidPosition(leftTile, priorTile))
		neightbors.push_back(leftTile);

	if (isAValidPosition(downTile, priorTile))
		neightbors.push_back(downTile);

	if (isAValidPosition(rightTile, priorTile))
		neightbors.push_back(rightTile);

	stable_sort(neightbors.begin(), neightbors.end(), [&](const PathmapTile* lhs, const PathmapTile* rhs){
		return distanceBtwTiles(lhs, aToTile) < distanceBtwTiles(rhs, aToTile);
		});

	aList.push_back(neightbors.at(0));

	return true;
// 
// 	map<Directions, PathmapTile*> arrayOfNeightbors;
// 	map<Directions, PathmapTile*> bestNeightbors;
//
// 	if (isAValidPosition(upTile, priorTile))
// 		arrayOfNeightbors[UP] = upTile;
// 
// 	if (isAValidPosition(leftTile, priorTile))
// 		arrayOfNeightbors[LEFT] = leftTile;
// 
// 	if (isAValidPosition(downTile, priorTile))
// 		arrayOfNeightbors[DOWN]= downTile;
// 
// 	if (isAValidPosition(rightTile, priorTile))
// 		arrayOfNeightbors[RIGHT] = rightTile;
// 
// 	Directions closestTileKey = NONE;
// 	int minDistance = 1000;
// 	bestNeightbors = arrayOfNeightbors;
// 
// 	// Intersection
// 	if (arrayOfNeightbors.size()>= 2)
// 	{
// 		for (auto const& [key, val] : arrayOfNeightbors)
// 		{
// 			int distance = (abs(aToTile->myX - val->myX) + abs(aToTile->myY - val->myY));
// 			if (minDistance > distance)
// 			{
// 				if (arrayOfNeightbors.find(closestTileKey)!= arrayOfNeightbors.end())
// 					bestNeightbors.erase(closestTileKey);
// 				closestTileKey = key;
// 				minDistance = distance;
// 			}
// 			else if (minDistance < distance)
// 			{
// 				bestNeightbors.erase(key);
// 			}
// 		}
// 		if (bestNeightbors.find(UP) != bestNeightbors.end())
// 			aList.push_back(bestNeightbors[UP]);
// 		else if (bestNeightbors.find(LEFT) != bestNeightbors.end())
// 			aList.push_back(bestNeightbors[LEFT]);
// 		else if (bestNeightbors.find(DOWN) != bestNeightbors.end())
// 			aList.push_back(bestNeightbors[DOWN]);
// 		else if (bestNeightbors.find(RIGHT) != bestNeightbors.end())
// 			aList.push_back(bestNeightbors[RIGHT]);
// 	}
// 	// Keep the same direction
// 	else
// 	{
// 		for (auto const& [key, val] : bestNeightbors)
// 			aList.push_back(val);
// 	}
}

//// IT WORKS
//bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, list<PathmapTile*>& aList)
//{
//	aFromTile->myIsVisitedFlag = true;
//	aList.push_back(aFromTile);
//
//	while (aFromTile != aToTile)
//	{
//		list<PathmapTile*> neighborList;
//		PathmapTile* up = GetTile(aFromTile->myX, aFromTile->myY - 1);
//		if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag)
//			neighborList.push_front(up);
//
//		PathmapTile* left = GetTile(aFromTile->myX - 1, aFromTile->myY);
//		if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag)
//			neighborList.push_front(left);
//
//		PathmapTile* down = GetTile(aFromTile->myX, aFromTile->myY + 1);
//		if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag)
//			neighborList.push_front(down);
//
//		PathmapTile* right = GetTile(aFromTile->myX + 1, aFromTile->myY);
//		if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag)
//			neighborList.push_front(right);
//
//		if (!neighborList.empty())
//		{
//			aFromTile = neighborList.front();
//			aFromTile->myIsVisitedFlag = true;
//			aList.push_back(aFromTile);
//		}
//		else if (!aList.empty())
//		{
//			aList.pop_back();
//			aFromTile = aList.back();
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	return true;
//}
// // ORIGINAL

//bool World::Pathfind(PathmapTile* aFromTile, PathmapTile* aToTile, std::list<PathmapTile*>& aList)
//{
//	aFromTile->myIsVisitedFlag = true;
//	if (aFromTile->myIsBlockingFlag)
//		return false;
//	if (aFromTile == aToTile)
//		return true;
//	std::list<PathmapTile*> neighborList;
//	PathmapTile* up = GetTile(aFromTile->myX, aFromTile->myY - 1);
//	if (up && !up->myIsVisitedFlag && !up->myIsBlockingFlag && ListDoesNotContain(up, aList))
//		neighborList.push_front(up);
//	PathmapTile* down = GetTile(aFromTile->myX, aFromTile->myY + 1);
//	if (down && !down->myIsVisitedFlag && !down->myIsBlockingFlag && ListDoesNotContain(down, aList))
//		neighborList.push_front(down);
//	PathmapTile* right = GetTile(aFromTile->myX + 1, aFromTile->myY);
//	if (right && !right->myIsVisitedFlag && !right->myIsBlockingFlag && ListDoesNotContain(right, aList))
//		neighborList.push_front(right);
//	PathmapTile* left = GetTile(aFromTile->myX - 1, aFromTile->myY);
//	if (left && !left->myIsVisitedFlag && !left->myIsBlockingFlag && ListDoesNotContain(left, aList))
//		neighborList.push_front(left);
//	neighborList.sort(SortFromGhostSpawn);
//	for (std::list<PathmapTile*>::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
//	{
//		PathmapTile* tile = *list_iter;
//		aList.push_back(tile);
//		if (Pathfind(tile, aToTile, aList))
//			return true;
//		aList.pop_back();
//	}
//	return false;
//}