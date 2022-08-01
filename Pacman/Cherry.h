#ifndef CHERRY_H
#define CHERRY_H

#include "StaticGameEntity.h"
#include "Vector2f.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class Cherry : public StaticGameEntity
{
public:
	Cherry(Vector2f aPosition, Sprite* entitySprite);
	~Cherry(void);
};

#endif // CHERRY_H