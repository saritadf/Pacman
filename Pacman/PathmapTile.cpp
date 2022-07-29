#ifdef _DEBUG
#define new MYDEBUG_NEW
#endif

#include "PathmapTile.h"

PathmapTile::PathmapTile(int anX, int anY, bool aIsBlockingFlag, bool aIsTunnelFlag, bool aIsBoxWallFlag)
: myX(anX)
, myY(anY)
, myIsBlockingFlag(aIsBlockingFlag)
, myIsVisitedFlag(false)
, myIsTunnelFlag(aIsTunnelFlag)
, myaIsBoxWallFlag(aIsBoxWallFlag)
{
}

PathmapTile::~PathmapTile(void)
{
}
