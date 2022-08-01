#ifndef DOT_H
#define DOT_H

#include "StaticGameEntity.h"
#include "Vector2f.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class Dot : public StaticGameEntity
{
public:
	Dot(Vector2f aPosition, Sprite* entitySprite);
	~Dot(void);
};

#endif // DOT_H