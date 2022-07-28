#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "MovableGameEntity.h"

MovableGameEntity::MovableGameEntity(const Vector2f& aPosition, Sprite* entitySprite)
: GameEntity(aPosition, entitySprite)
{
	Respawn(aPosition);
}

MovableGameEntity::~MovableGameEntity(void)
{
}

bool MovableGameEntity::IsAtDestination()
{
	if (myCurrentTileX == myNextTileX && myCurrentTileY == myNextTileY)
	{


		return true;
	}

	return false;
}

void MovableGameEntity::SetNextTile(int anX, int anY)
{
	myNextTileX = anX;
	myNextTileY = anY;
}

void MovableGameEntity::Respawn(const Vector2f& aPosition)
{
	SetPosition(aPosition);
	myCurrentTileX = myNextTileX =  myPosition.myX / TILE_SIZE;
	myCurrentTileY = myNextTileY =  myPosition.myY / TILE_SIZE;
}