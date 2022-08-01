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
	if (myGhostType == Red)
	{
		sprite->SetFrame(ASSET_PATH_RED_GHOST);
	}
	else if (myGhostType == Pink)
	{
		sprite->SetFrame(ASSET_PATH_PINK_GHOST);
	}
	else if (myGhostType == Orange)
	{
		sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
	}
	else if (myGhostType == Cyan)
	{
		sprite->SetFrame(ASSET_PATH_CYAN_GHOST);
	}

	myIsVulnerableFlag = false;
	myIsDeadFlag = false;
	myIsChaseMode = false;
	speed = 140;
	myDesiredMovementX = 0;
	myDesiredMovementY = 0;
}

Ghost::~Ghost(void)
{
}

bool isInsideTheBox(int tileX, int tileY)
{
	return (tileX > MIN_RANGE_TILEX) && (tileX < MAX_RANGE_TILEX)
		&& (tileY > MIN_RANGE_TILEY) && (tileY < MAX_RANGE_TILEY);
}

void CheckLimitValues(int& targetX, int& targetY)
{
	targetX = targetX > 25 ? 25 : targetX;
	targetX = targetX < 0 ? 0 : targetX;
	targetY = targetY > 28 ? 28 : targetY;
	targetY = targetY < 0 ? 0 : targetY;
}

void Ghost::SetRedGhostPosition(Vector2f posX)
{
	redGhostPos.myX = posX.myX /TILE_SIZE;
	redGhostPos.myY = posX.myY /TILE_SIZE;
}

void Ghost::Update(float aTime, World* aWorld, Avatar* avatar)
{
	if (!myIsDeadFlag && !myIsVulnerableFlag)
	{
		if (myGhostType == Red)
		{
			sprite->SetFrame(ASSET_PATH_RED_GHOST);
		}
		else if (myGhostType == Pink)
		{
		sprite->SetFrame(ASSET_PATH_PINK_GHOST);
		}
		else if (myGhostType == Orange)
		{
		sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
		}
		else if (myGhostType == Cyan)
		{
			sprite->SetFrame(ASSET_PATH_CYAN_GHOST);
		}

		if (myIsChaseMode)
		{
			myBehavior = Chase;
			myIsChaseMode = false;
		}
		else
			myBehavior = Scatter;
	}

	if (myIsDeadFlag)
	{
		speed = DEAD_SPEED;

		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);
		sprite->SetFrame(ASSET_PATH_GHOST_DEAD);

		myBehavior = Fear;
		myIsVulnerableFlag = false;
	}
	else if (!myIsVulnerableFlag)
		speed = REGULAR_SPEED;

	// The ghost is inside the box
	if (isInsideTheBox(myCurrentTileX, myCurrentTileY))
	{
		myBehavior = Intercept;

		if (myGhostType == Red)
		{
			sprite->SetFrame(ASSET_PATH_RED_GHOST);
		}
		else if (myGhostType == Pink)
		{
			sprite->SetFrame(ASSET_PATH_PINK_GHOST);
		}
		else if (myGhostType == Orange)
		{
			sprite->SetFrame(ASSET_PATH_ORANGE_GHOST);
		}
		else if (myGhostType == Cyan)
		{
			sprite->SetFrame(ASSET_PATH_CYAN_GHOST);
		}

		myIsDeadFlag = false;
		myIsVulnerableFlag = false;
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
			if (myIsVulnerableFlag)
			{
				BehaveVulnerable(aWorld, GhostType::All);
				speed = VULNERABLE_SPEED;
			}
			else
			{
				switch (myBehavior)
				{
				case Chase:
					BehaveChase(aWorld, avatar, myGhostType);
					break;
				case Intercept:
					BehaveIntercept(aWorld, OUTSIDE_BOX_POSX, OUTSIDE_BOX_POSY, GhostType::All);
					if(myCurrentTileX == OUTSIDE_BOX_POSX && myCurrentTileY == OUTSIDE_BOX_POSY)
						myBehavior = Scatter;
					break;
				case Fear:
					BehaveFear(aWorld, PINK_GHOST_POSX, PINK_GHOST_POSY, GhostType::All);
					break;
				case Scatter:
					BehaveScatter(aWorld, avatar, myGhostType);
					break;
				default:
					BehaveScatter(aWorld, avatar, myGhostType);
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
	// Normalize direction
	else
	{
		direction.Normalize();
		myPosition += direction * distanceToMove;
	}
}

GhostType Ghost::GetGhostType()
{
	return myGhostType;
}

void Ghost::SetImage(string anImage)
{
	sprite->SetFrame(anImage);
}

void Ghost::BehaveScatter(World* aWorld, Avatar* avatar, GhostType ghostType)
{
	int targetX = 0, targetY = 0;

	if (myGhostType == Red)
	{
		targetX = 23;
		targetY = 0;
	}
	else if (myGhostType == Pink)
	{
		targetX = 2;
		targetY = 0;
	}
	else if (myGhostType == Orange)
	{
		targetX = 7;
		targetY = 22;
	}
	else if (myGhostType == Cyan)
	{
		targetX = 19;
		targetY = 22;
	}

	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, targetX, targetY, myPath, myPriorTileX, myPriorTileY, myBehavior, ghostType);
}

void Ghost::BehaveIntercept(World* aWorld, int targetX, int targetY, GhostType ghostType)
{
	myPath.clear();
	aWorld->GetPath(myCurrentTileX, myCurrentTileY, targetX, targetY, myPath, myPriorTileX, myPriorTileY, myBehavior, ghostType);
}

int distanceBtwTiles(const int dx, const int dy)
{
	return abs (dx - dy);
}

void Ghost::BehaveChase(World* aWorld, Avatar* avatar, GhostType ghostType)
{
	int targetX = 0, targetY = 0;
	if (myGhostType == Red)
	{
		targetX = avatar->GetCurrentTileX();
		targetY = avatar->GetCurrentTileY();
	}
	else if (myGhostType == Pink)
	{
		int addToTargetX;
		int addToTargetY;

		//Going  Right / Left
		if (avatar->GetPriorTileX() == avatar->GetCurrentTileX())
			addToTargetX = 0;
		else
			addToTargetX = avatar->GetPriorTileX() < avatar->GetCurrentTileX() ? 2 : -2;

		//Going  Down / Up
		if (avatar->GetPriorTileY() == avatar->GetCurrentTileY())
			addToTargetY = 0;
		else
			addToTargetY = avatar->GetPriorTileY() < avatar->GetCurrentTileY() ? 2 : -4;

		targetX = avatar->GetCurrentTileX() + addToTargetX;
		targetY = avatar->GetCurrentTileY() + addToTargetY;

		// Going Up (original overflow error)
		if (avatar->GetPriorTileY() > avatar->GetCurrentTileY())
			addToTargetX = -4;

		targetX = avatar->GetCurrentTileX() + addToTargetX;
		targetY = avatar->GetCurrentTileY() + addToTargetY;
	}
	else if (myGhostType == Orange)
	{
		if (abs(myCurrentTileX - avatar->GetCurrentTileX()) <= 8 && abs(myCurrentTileY - avatar->GetCurrentTileY()) <= 8)
		{
			targetX = 7;
			targetY = 22;
		}
		else
		{
			targetX = avatar->GetCurrentTileX();
			targetY = avatar->GetCurrentTileY();
		}
	}
	else if (myGhostType == Cyan)
	{
		int addToTargetX;
		int addToTargetY;

		//Going  Right / Left
		if (avatar->GetPriorTileX() == avatar->GetCurrentTileX())
			addToTargetX = 0;
		else		
			addToTargetX = avatar->GetPriorTileX() < avatar->GetCurrentTileX() ? 2 : -2;

		//Going  Down / Up
		if (avatar->GetPriorTileY() == avatar->GetCurrentTileY())
			addToTargetY = 0;
		else
			addToTargetY = avatar->GetPriorTileY() < avatar->GetCurrentTileY() ? 2 : -2;

		targetX = avatar->GetCurrentTileX() + addToTargetX;
		targetY = avatar->GetCurrentTileY() + addToTargetY;

		if (redGhostPos.myX > avatar->GetCurrentTileX())
			targetX = targetX - distanceBtwTiles(redGhostPos.myX, targetX);
		else
			targetX = targetX + distanceBtwTiles(redGhostPos.myX, targetX);

		if (redGhostPos.myY < avatar->GetCurrentTileY())
			targetY = targetY + distanceBtwTiles(redGhostPos.myY, targetY);
		else
			targetY = targetY - distanceBtwTiles(redGhostPos.myY, targetY);
	}

	CheckLimitValues(targetX, targetY);
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

	aWorld->GetPath(myCurrentTileX, myCurrentTileY, -1, -1, myPath, myPriorTileX, myPriorTileY, Vulnerable, ghostType);
}