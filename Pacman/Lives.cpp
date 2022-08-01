#include "Lives.h"

Lives::Lives(Vector2f aPosition, Sprite* entitySprite)
	: StaticGameEntity(aPosition, entitySprite)
{
	sprite->SetFrame(ASSET_PATH_LIVES_AVATAR);
}

Lives::~Lives(void)
{
}

