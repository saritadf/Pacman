#ifndef CHERRY_H
#define CHERRY_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

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