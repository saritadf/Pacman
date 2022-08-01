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
	sprite->SetFrame(ASSET_PATH_RED_GHOST);
	sprite->SetFrame(ASSET_PATH_PINK_GHOST);
	sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
	sprite->SetFrame(ASSET_PATH_CYAN_GHOST);

	SetPosition(aPosition);
	myCurrentTileX = myNextTileX =  myPosition.myX / TILE_SIZE;
	myCurrentTileY = myNextTileY =  myPosition.myY / TILE_SIZE;
}