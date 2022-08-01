#include "Sound.h"

Sound* Sound::Create(SDL_Window* aWindow, SDL_Renderer* aRenderer)
{
	Sound* drawer = new Sound(aWindow, aRenderer);

	if (!drawer->Init())
	{
		delete drawer;
		drawer = NULL;
	}

	return drawer;
}

Sound::Sound(SDL_Window* aWindow, SDL_Renderer* aRenderer)
	: myWindow(aWindow)
	, myRenderer(aRenderer)
{
}

Sound::~Sound(void)
{
}

bool Sound::Init()
{
	if (!myWindow)
		return false;

	return true;
}

SDL_Texture* Sound::GetTextureResource(string assetPath)
{
	SDL_Texture* texture = NULL;
	SDL_Texture* spriteSheetTexture = NULL;
	SDL_Surface* surface = NULL;

	map<string, SDL_Texture*>::iterator textureFinder = textures.find(assetPath);
	if (textureFinder != textures.end())
		texture = textureFinder->second;
	else
	{
		texture = IMG_LoadTexture(myRenderer, assetPath.c_str());
		textures[assetPath] = texture;
	}

	return texture;
}
