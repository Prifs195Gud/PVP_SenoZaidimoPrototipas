#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <vector>

// Paprasta klase, kuri saugo kur yra teksturos kvadrato duomenys
// Is esmes tas pats kas SDL_Rect, bet patogiau naudotis
class Sprite
{
private:
	SDL_Rect textureData; // cia nusako kur tas kvadratelis kurio man reikaia yra teksturos faile
public:

	Sprite();
	Sprite(SDL_Rect data);
	Sprite(int posX, int posY, int width, int height);
	Sprite(Vector2 texturePosition, int Width, int Height);
	Sprite(Vector2 texturePosition, Vector2 widthHeight);

	~Sprite();

	SDL_Rect* GetTextureData();
	Vector2 GetTexturePosition();
	int GetTextureWidth();
	int GetTextureHeight();
};