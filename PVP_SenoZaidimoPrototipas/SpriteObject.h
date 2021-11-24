#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <Sprite.h>
#include <list>
#include <unordered_map>
#include <Transform.h>
#include <Tick.h>

using namespace std;

// Kokiam sluoksnyje bus SpriteObject, kad galetu graziai vienas ant kito uzlipti dalykai
enum class LayerType
{
	Background = -1,
	Default = 0,
	MapTiles = 1,
	Overlay = 2,
	Debug = 3
};

// Klase skirta, kad butent galetum jau atvaizduoti objekta, ji judinti ar kitaip manipuliuoti
class SpriteObject : public Transform
{
private:
	static vector<SpriteObject*> allObjects;
	static unordered_map<int, vector<SpriteObject*>> objectLayers;

	bool renderingEnabled;
	int layer;

	void Initialize(int Layer);

protected:
	Sprite sprite;
	SDL_Rect renderData; // Cia skirta, kad galetu ant lango tinkamai pavaizduoti kvadrateli

	bool markedForDeletion; // jei reikes trinti atsargiai, tai sita naudosime

public:
	SpriteObject();
	SpriteObject(Sprite Sprite);
	SpriteObject(Sprite Sprite, int layer);

	~SpriteObject();

	static vector<SpriteObject*>* GetAllObjects();
	static unordered_map<int, vector<SpriteObject*>>* GetAllLayers();

	void Enable(bool var);
	bool IsEnabled();

	bool IsMarkedForDeletion();
	void MarkForDeletion();

	SDL_Rect* GetTextureData();
	SDL_Rect* GetRenderData();

	void UpdateRenderData(Vector2 worldScale);
	virtual void OnRenderDataChange();

	void Tick() override;
	void OnPositionChange() override;

	void SetSprite(Sprite SPRITE);
	void SetLayer(LayerType newLayer);
	void SetLayer(int newLayer);
};