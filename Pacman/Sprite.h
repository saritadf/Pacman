#ifndef SPRITE_H
#define SPRITE_H

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