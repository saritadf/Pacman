#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

#include "Vector2f.h"
#include "Sprite.h"

class Drawer;

class GameEntity
{
public:
	GameEntity(const Vector2f& aPosition, Sprite* entitySprite);
	~GameEntity(void);

	Vector2f GetPosition() const { return myPosition; }
	void SetPosition(const Vector2f& aPosition){ myPosition = aPosition; }

	bool Intersect(GameEntity* aGameEntity);
	virtual void Draw(Drawer* aDrawer);

	void MarkForDelete() { myIdMarkedForDeleteFlag = true; }
	bool IsMarkedForDelete() const { return myIdMarkedForDeleteFlag; }

protected:

	Sprite* sprite;
	bool myIdMarkedForDeleteFlag;
	Vector2f myPosition;
};

#endif // GAMEENTITY_H