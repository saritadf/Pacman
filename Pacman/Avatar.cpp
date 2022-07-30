#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "Avatar.h"

Avatar::Avatar(const Vector2f& aPosition, Sprite* entitySprite)
: MovableGameEntity(aPosition, entitySprite)
{
	sprite->SetFrame(ASSET_PATH_LEFT_AVATAR);
}

Avatar::~Avatar(void)
{
}

void Avatar::Initialize()
{
	sprite->SetFrame(ASSET_PATH_LEFT_AVATAR);
}

void Avatar::Update(float aTime)
{
	SDL_Texture* texture = NULL;

	Vector2f destination(float(myNextTileX * TILE_SIZE), float(myNextTileY * TILE_SIZE));
	Vector2f direction = destination - myPosition;

	if (direction.myX < 0)
	{
		sprite->SetFrame(ASSET_PATH_LEFT_AVATAR);
	}
	else if (direction.myX > 0)
	{ 
		sprite->SetFrame(ASSET_PATH_RIGHT_AVATAR);
	}
	else if (direction.myY > 0)
	{
		sprite->SetFrame(ASSET_PATH_DOWN_AVATAR);
	}
	else if (direction.myY < 0)
	{
		sprite->SetFrame(ASSET_PATH_UP_AVATAR);
	}

	float distanceToMove = aTime * AVATAR_SPEED;

	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		myPriorTileX = myCurrentTileX;
		myPriorTileY = myCurrentTileY;
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
}
