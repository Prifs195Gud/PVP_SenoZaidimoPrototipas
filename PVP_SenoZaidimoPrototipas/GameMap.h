#pragma once

#include <string>
#include <Sprite.h>
#include <SpriteObject.h>
#include <Collision.h>
#include <vector>

using namespace std;

enum class MapTileType
{
	Ground = 0,
	Brick,
	Empty,
	CoinBlock
};

class MapTile : public StaticCollidable
{
public:
	MapTile(MapTileType tileType);
	MapTile(Sprite sprite, MapTileType tileType);
	~MapTile();

	//FinalObjectType GetFinalObjectType() override;
	MapTileType GetMapTileType();
private:
	MapTileType mapTileType;
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