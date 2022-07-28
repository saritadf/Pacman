#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"
#include "Avatar.h"

Ghost::Ghost(const Vector2f& aPosition, Sprite* entitySprite, GhostBehavior behavior)
	: MovableGameEntity(aPosition, entitySprite),
	myBehavior(behavior)
{
	sprite->SetFrame(ASSET_PATH_RED_GHOST);
	//sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
	//sprite->SetFrame(ASSET_PATH_PINK_GHOST);
	//sprite->SetFrame(ASSET_PATH_CYAN_GHOST);

	myIsClaimableFlag = false;
	myIsDeadFlag = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = -1;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, PINK_GHOST_POSX, PINK_GHOST_POSY, myPath, myPriorTileX, myPriorTileY);
	sprite->SetFrame(ASSET_PATH_RED_GHOST);
	//sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
	//sprite->SetFrame(ASSET_PATH_PINK_GHOST);
	//sprite->SetFrame(ASSET_PATH_CYAN_GHOST);
}

void Ghost::Update(float aTime, World* aWorld, Avatar* avatar)
{
	float speed = 150.f;
	int nextTileX = myCurrentTileX + myDesiredMovementX;
	int nextTileY = myCurrentTileY + myDesiredMovementY;

	if (myIsDeadFlag)
	{
		speed = 120.f;
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
	}
	else
	{
		if (myIsClaimableFlag)
			BehaveVulnerable();
	}

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();
			SetNextTile(nextTile->myX, nextTile->myY);

			//myDesiredMovementX = myNextTileX - myCurrentTileX;
			//myDesiredMovementY = myNextTileY - myCurrentTileY;
		}
		else if (aWorld->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);

			//myDesiredMovementX = myNextTileX - myCurrentTileX;
			//myDesiredMovementY = myNextTileY - myCurrentTileY;
		}
		else
		{
			if (myIsClaimableFlag)
				BehaveVulnerable();
			else
			{
				sprite->SetFrame(ASSET_PATH_RED_GHOST);
				//sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
				//sprite->SetFrame(ASSET_PATH_PINK_GHOST);
				//sprite->SetFrame(ASSET_PATH_CYAN_GHOST);

				switch (myBehavior)
				{
				case Chase:
					BehaveChase(aWorld, avatar);
					break;
				case Intercept:
					BehaveIntercept(aWorld, avatar);
				case Fear:
				case Wander:
				default:
					BehaveWander();
					break;
				}
			}

			myIsDeadFlag = false;
		}
	}

	Vector2f destination(float(myNextTileX * TILE_SIZE), float(myNextTileY * TILE_SIZE));
	direction = destination - myPosition;

	float distanceToMove = aTime * speed;

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

void Ghost::SetImage(string anImage)
{
	sprite->SetFrame(anImage);
}

void Ghost::BehaveWander()
{/*
	MovementDirection nextDirection = (MovementDirection)(rand() % DirectionCount);
	switch (nextDirection)
	{
	case Up:
		myDesiredMovementX = 0;
		myDesiredMovementY = 1;
		break;
	case Down:
		myDesiredMovementX = 0;
		myDesiredMovementY = -1;
		break;
	case Left:
		myDesiredMovementX = -1;
		myDesiredMovementY = 0;
		break;
	case Right:
		myDesiredMovementX = 1;
		myDesiredMovementY = 0;
		break;
	default:
		break;
	}*/
}

void Ghost::BehaveChase(World* aWorld, Avatar* avatar)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, avatar->GetCurrentTileX(), avatar->GetCurrentTileY(), myPath, myPriorTileX, myPriorTileY);
}

void Ghost::BehaveIntercept(World* aWorld, Avatar* avatar)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, avatar->GetCurrentTileX()+4, avatar->GetCurrentTileY()+4, myPath, myPriorTileX, myPriorTileY);
}

void Ghost::BehaveFear(World* aWorld, Avatar* avatar)
{

}

void Ghost::BehaveVulnerable()
{
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
}