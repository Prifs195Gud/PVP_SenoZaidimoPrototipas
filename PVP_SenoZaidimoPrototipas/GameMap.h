#pragma once

#include <string>
#include <Sprite.h>
#include <SpriteObject.h>
#include <Collision.h>
#include <vector>

using namespace std;

class MapTile : public StaticCollidable
{
public:
	MapTile(Sprite sprite);
	MapTile(Sprite sprite, LayerType layerType);
	~MapTile();

	FinalObjectType GetFinalObjectType() override;
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	static GameMap* GetReference();

	vector<MapTile*>* GetMapTiles();

	void LoadMap(int world, int level);
	void ClearMap();
private:
	static GameMap* singleton;

	vector<MapTile*> MapTiles;

	void ReadMapLine(string* line);
};