#include "Cherry.h"

Cherry::Cherry(Vector2f aPosition, Sprite* entitySprite)
: StaticGameEntity(aPosition, entitySprite)
{
	sprite->SetFrame(ASSET_PATH_CHERRY);
}

Cherry::~Cherry(void)
{
}
