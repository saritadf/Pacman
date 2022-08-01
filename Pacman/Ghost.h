#ifndef GHOST_H
#define GHOST_H

#include <list>
#include "MovableGameEntity.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class World;
class PathmapTile;
class Avatar;

class Ghost : public MovableGameEntity
{
public:
	Ghost(const Vector2f& aPosition, Sprite* entitySprite, GhostBehavior behavior, GhostType ghostType);
	~Ghost(void);

	void Update(float aTime, World* aWorld, Avatar* avatar);
	void SetRedGhostPosition(Vector2f posX);

	bool myIsVulnerableFlag;
	bool myIsDeadFlag;
	bool myIsChaseMode;
	Vector2f redGhostPos;

	void SetImage(string anImage);
	GhostType GetGhostType();

protected:
	void BehaveScatter(World* aWorld, Avatar* avatar, GhostType ghostType);
	void BehaveChase(World* aWorld, Avatar* avatar, GhostType ghostType);
	void BehaveIntercept(World* aWorld, int targetX, int targetY, GhostType ghostType);
	void BehaveFear(World* aWorld, int targetX, int targetY, GhostType ghostType);
	void BehaveVulnerable(World* aWorld, GhostType ghostType);

	GhostBehavior myBehavior;
	GhostType myGhostType;
	int myDesiredMovementX;
	int myDesiredMovementY;
	float speed;

	const int VULNERABLE_SPEED = 75.f;
	const int DEAD_SPEED = 170.f;
	const int REGULAR_SPEED = 140.f;

	list<PathmapTile*> myPath;

};

#endif // GHOST_H