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
	enum GhostBehavior
	{
		Wander,
		Chase,
		Intercept,
		Fear,
	};

	Ghost(const Vector2f& aPosition, Sprite* entitySprite, GhostBehavior behavior);
	~Ghost(void);

	void Update(float aTime, World* aWorld, Avatar* avatar);

	bool myIsClaimableFlag;
	bool myIsDeadFlag;

	void SetImage(string anImage);

	void Die(World* aWorld);

protected:
	void BehaveWander();
	void BehaveChase(World* aWorld, Avatar* avatar);
	void BehaveIntercept(World* aWorld, Avatar* avatar);
	void BehaveFear(World* aWorld, Avatar* avatar);
	void BehaveVulnerable();

	GhostBehavior myBehavior;
	int myDesiredMovementX;
	int myDesiredMovementY;

	list<PathmapTile*> myPath;

};

#endif // GHOST_H