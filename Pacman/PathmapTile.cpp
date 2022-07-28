#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "PathmapTile.h"

PathmapTile::PathmapTile(int anX, int anY, bool aIsBlockingFlag, bool aIsTunelFlag)
: myX(anX)
, myY(anY)
, myIsBlockingFlag(aIsBlockingFlag)
, myIsVisitedFlag(false)
, myIsTunelFlag(aIsTunelFlag)
{
}

PathmapTile::~PathmapTile(void)
{
}
