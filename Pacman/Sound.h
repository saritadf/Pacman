#pragma once
#ifndef SOUND_H
#define SOUND_H

using namespace std;

class Sound
{
public:
	static Sound* Create(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Sound(void);

	SDL_Texture* GetTextureResource(string assetPath);
	SDL_Texture* GetTextureResource(SDL_Surface* surface);
	TTF_Font* GetFontResource(string assetPath, int size);

	void Draw(SDL_Texture* texture, SDL_Rect frame, int aCellX, int aCellY);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);

private:
	Sound(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	bool Init();

	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	SDL_Surface* world;

	map<string, SDL_Texture*> textures;
	map<string, TTF_Font*> fonts;
};

#endif // SOUND_H
