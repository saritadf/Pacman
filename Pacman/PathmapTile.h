#ifndef PATHMAPTILE_H
#define PATHMAPTILE_H

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