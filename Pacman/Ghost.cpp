#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "Ghost.h"
#include "World.h"
#include "PathmapTile.h"
#include "Drawer.h"
#include "Avatar.h"

Ghost::Ghost(const Vector2f& aPosition, Sprite* entitySprite, GhostBehavior behavior, GhostType ghostType)
	: MovableGameEntity(aPosition, entitySprite),
	myBehavior(behavior),
	myGhostType(ghostType)
{
	sprite->SetFrame(ASSET_PATH_RED_GHOST);
	sprite->SetFrame(ASSET_PATH_PINK_GHOST);
	//sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
	//sprite->SetFrame(ASSET_PATH_CYAN_GHOST);

	myIsClaimableFlag = false;
	myIsDeadFlag = false;
	myIsChaseMode = false;
	myIsScatterMode = false;

	myDesiredMovementX = 0;
	myDesiredMovementY = 0;
}

Ghost::~Ghost(void)
{
}

void Ghost::Die(World* aWorld)
{
	return (tileX > MIN_RANGE_TILEX) && (tileX < MAX_RANGE_TILEX)
		&& (tileY > MIN_RANGE_TILEY) && (tileY < MAX_RANGE_TILEY);
}

void Ghost::Update(float aTime, World* aWorld, Avatar* avatar)
{
	float speed = 100.f;

	if (myIsDeadFlag)
	{
		speed = 150.f;
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
		myBehavior = Fear;
	}
	// The ghost is inside the box
	if (isInsideTheBox(myCurrentTileX, myCurrentTileY))
	{
		myBehavior = Intercept;
		sprite->SetFrame(ASSET_PATH_RED_GHOST);
		myIsDeadFlag = false;
	}
	if ((myIsChaseMode || myIsScatterMode) && !myIsDeadFlag && !myIsClaimableFlag)
	{
		sprite->SetFrame(ASSET_PATH_RED_GHOST);
		sprite->SetFrame(ASSET_PATH_PINK_GHOST);
		//sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
		//sprite->SetFrame(ASSET_PATH_CYAN_GHOST);
	}

	if (IsAtDestination())
	{
		if (!myPath.empty())
		{
			PathmapTile* nextTile = myPath.front();
			myPath.pop_front();

			if (nextTile->myIsTunnelFlag && (myPriorTileX == RIGHT_TUNNEL_TILEX
				|| myPriorTileX == LEFT_TUNNEL_TILEX))
			{
				// Entered by the left side of the Tunnel
				if (myCurrentTileX < nextTile->myX)
					Respawn(Vector2f(RIGHT_TUNNEL_TILEX * TILE_SIZE, nextTile->myY * TILE_SIZE));
				else
					Respawn(Vector2f(LEFT_TUNNEL_TILEX * TILE_SIZE, nextTile->myY * TILE_SIZE));
			}

			SetNextTile(nextTile->myX, nextTile->myY);
		}
		else
		{
			if (myIsClaimableFlag)
				BehaveVulnerable(aWorld, GhostType::All);
			else
			{
				switch (myBehavior)
				{
				case Chase:
					int targetX, targetY;
					if (myGhostType == Red)
					{
						targetX = avatar->GetCurrentTileX();
						targetY = avatar->GetCurrentTileY();
					}
					else if (myGhostType == Pink)
					{
						targetX = avatar->GetCurrentTileX()+2;
						targetY = avatar->GetCurrentTileY()+2;
					}
					else if (myGhostType == Orange)
					{

					}
					else if (myGhostType == Cyan)
					{

					}
					targetX = targetX > 25 ? 25 : targetX;
					targetX = targetX < 0 ? 0 : targetX;
					targetY = targetY > 28 ? 28 : targetY;
					targetY = targetY < 0 ? 0 : targetY;

					BehaveChase(aWorld, targetX, targetY, myGhostType);
					break;
				case Intercept:
					BehaveChase(aWorld, OUTSIDE_BOX_POSX, OUTSIDE_BOX_POSY, GhostType::All);
					if(myCurrentTileX == OUTSIDE_BOX_POSX && myCurrentTileY == OUTSIDE_BOX_POSY)
						myBehavior = Chase;
					break;
				case Fear:
					BehaveFear(aWorld, PINK_GHOST_POSX, PINK_GHOST_POSY, GhostType::All);
					break;
				case Wander:
				default:
					BehaveWander();
					break;
				}
			}
		}
	}

	Vector2f destination(float(myNextTileX * TILE_SIZE), float(myNextTileY * TILE_SIZE));
	direction = destination - myPosition;

	float distanceToMove = aTime * speed;

	// if movement (direction) is smaller than it is possible to be moved (distanceToMove)
	if (distanceToMove > direction.Length())
	{
		myPosition = destination;
		
		myPriorTileX = myCurrentTileX;
		myPriorTileY = myCurrentTileY;
		
		myCurrentTileX = myNextTileX;
		myCurrentTileY = myNextTileY;
	}
	// else normalize direction
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
{
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
	}
}

void Ghost::BehaveChase(World* aWorld, int targetX, int targetY, GhostType ghostType)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, targetX, targetY, myPath, myPriorTileX, myPriorTileY, myBehavior,ghostType);
}

void Ghost::BehaveFear(World* aWorld, int targetX, int targetY, GhostType ghostType)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, targetX, targetY, myPath, myPriorTileX, myPriorTileY, Fear, ghostType);
}

void Ghost::BehaveVulnerable(World* aWorld, GhostType ghostType)
{
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);
	sprite->SetFrame(ASSET_PATH_GHOST_VULNERABLE);

	MovementDirection nextDirection = (MovementDirection)(rand() % DirectionCount);
	switch (nextDirection)
	{
	case Up:
		if (aWorld->TileIsValid(myCurrentTileX, myCurrentTileY +1))
			myNextTileY = myCurrentTileY +1;
		break;
	case Down:
		if (aWorld->TileIsValid(myCurrentTileX, myCurrentTileY -1))
			myNextTileY = myCurrentTileY -1;
		break;
	case Left:
		if (aWorld->TileIsValid(myCurrentTileX -1, myCurrentTileY ))
			myNextTileX = myCurrentTileX -1;
		break;
	case Right:
		if (aWorld->TileIsValid(myCurrentTileX + 1, myCurrentTileY))
			myNextTileX = myCurrentTileX + 1;
		break;
	default:
		break;
	}
}