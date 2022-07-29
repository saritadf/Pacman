#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

class PathmapTile
{
public:
	PathmapTile(int anX, int anY, bool aIsBlockingFlag, bool aIsTunnelFlag, bool aIsBoxWallFlag);
	~PathmapTile(void);

	int myX;
	int myY;
	bool myIsBlockingFlag;
	bool myIsVisitedFlag;
	bool myIsTunnelFlag;
	bool myaIsBoxWallFlag;

};

#endif // PATHMAPTILE_H