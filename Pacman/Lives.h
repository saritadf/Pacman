#ifndef LIVES_H
#define LIVES_H

#include "StaticGameEntity.h"
#include "Vector2f.h"
#include "Constants.h"

using namespace constants;
using namespace std;

class Lives : public StaticGameEntity
{
public:
	Lives(Vector2f aPosition, Sprite* entitySprite);
	~Lives(void);
};

#endif // LIVES_H