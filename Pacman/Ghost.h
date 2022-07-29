#ifndef GHOST_H
#define GHOST_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

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
	bool myIsScatterMode;
	Vector2f redGhostPos;

	void SetImage(string anImage);
	GhostType GetGhostType();

protected:
	void BehaveWander(World* aWorld, Avatar* avatar, GhostType ghostType);
	void BehaveChase(World* aWorld, Avatar* avatar, GhostType ghostType);
	void BehaveIntercept(World* aWorld, int targetX, int targetY, GhostType ghostType);
	void BehaveFear(World* aWorld, int targetX, int targetY, GhostType ghostType);
	void BehaveVulnerable(World* aWorld, GhostType ghostType);

	GhostBehavior myBehavior;
	GhostType myGhostType;
	int myDesiredMovementX;
	int myDesiredMovementY;

	list<PathmapTile*> myPath;

};

#endif // GHOST_H