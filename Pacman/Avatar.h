#ifndef AVATAR_H
#define AVATAR_H

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

private:
	const int AVATAR_SPEED = 140.0f;
};

#endif //AVATAR_H