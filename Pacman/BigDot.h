#ifndef BIGDOT_H
#define BIGDOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class BigDot : public StaticGameEntity
{
public:
	BigDot(Vector2f aPosition, Sprite* entitySprite);
	~BigDot(void);
};

#endif // BIGDOT_H