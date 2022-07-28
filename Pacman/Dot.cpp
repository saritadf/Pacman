#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "Dot.h"

Dot::Dot(Vector2f aPosition, Sprite* entitySprite)
: StaticGameEntity(aPosition, entitySprite)
{
	sprite->SetFrame(ASSET_PATH_SMALL_DOT);
}

Dot::~Dot(void)
{
}
