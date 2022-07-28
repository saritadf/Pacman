#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "BigDot.h"

BigDot::BigDot(Vector2f aPosition, Sprite* entitySprite)
: StaticGameEntity(aPosition, entitySprite)
{
	sprite->SetFrame(ASSET_PATH_BIG_DOT);
}

BigDot::~BigDot(void)
{
}
