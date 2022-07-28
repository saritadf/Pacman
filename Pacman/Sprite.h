#ifndef SPRITE_H
#define SPRITE_H

#ifdef _DEBUG
#define MYDEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
//allocations to be of _CLIENT_BLOCK type
#else
#define MYDEBUG_NEW
#endif

#include <list>
#include <map>
#include "SDL_image.h"
#include "SDL_rect.h"
#include <string>

using namespace std;

struct SDL_Texture;
class Drawer;

class Sprite
{
public:
	static Sprite* Create(list<string> assetPaths, Drawer* drawer, int sizeX, int sizeY);
	~Sprite(void);

	void SetFrame(string frameKey);
	void Draw(Drawer* drawer, int posX, int posY);
	string Sprite::GetFrame();
	map<string, SDL_Texture*> Sprite::GetTextures();

private:
	Sprite(map<string, SDL_Texture*> frameCollection, SDL_Rect sizeRect);
	
	map<string, SDL_Texture*> textures;
	string currentFrame;
	SDL_Rect frame;
};

#endif // SPRITE_H