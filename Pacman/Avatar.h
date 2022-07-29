#ifndef AVATAR_H
#define AVATAR_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

#include "MovableGameEntity.h"
#include "Vector2f.h"
#include "Drawer.h"
#include "Pacman.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class Avatar : public MovableGameEntity
{
public:
	Avatar(const Vector2f& aPosition, Sprite* entitySprite);
	~Avatar(void);

	void Initialize();
	void Update(float aTime);
};

#endif //AVATAR_H