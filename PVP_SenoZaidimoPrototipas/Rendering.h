#pragma once

#include <Sprite.h>
#include <SDL.h>
#include <Vectors.h>
#include <vector>
#include <SpriteObject.h>
#include <unordered_map>

using namespace std;

class Rendering
{
public:
	Rendering();
	~Rendering();

	static Rendering* GetReference();

	Vector2 GetRenderScale();

	void RenderWindow();
	void SetTileset(SDL_Texture* tileset_);
	void SetRenderer(SDL_Renderer* renderer);

	SDL_Renderer* GetRenderer();
	Sprite GetLetterTexture(char letter);
	vector<Sprite>* GetLetterTextures();

private:
	static Rendering* singleton;

	SDL_Texture* tileset;
	SDL_Renderer* mainRenderer;

	const Vector2 renderScale = Vector2(4.0, 4.0);

	vector<Sprite> lettersData;
	unordered_map<char, size_t> lettersHashmap;

	void InitializeMapTiles();
	void InitializeFont();
	
	void DrawMapBackground();
	void RenderAllObjects();

	Vector2 GetDesktopResolution();
};