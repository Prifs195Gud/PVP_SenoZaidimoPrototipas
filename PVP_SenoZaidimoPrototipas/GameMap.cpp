#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <Rendering.h>

MapTile::MapTile(Sprite sprite, MapTileType tileType)// : StaticCollidable(sprite, layerType::MapTiles), mapTileType(tileType)
{
}

MapTile::~MapTile()
{
}

/*FinalObjectType MapTile::GetFinalObjectType() // override StaticCollidable
{
	return FinalObjectType::MapTile;
}*/

MapTileType MapTile::GetMapTileType()
{
	return mapTileType;
}

// ***************************************************

GameMap* GameMap::singleton = nullptr;

GameMap::GameMap()
{
	if (singleton == nullptr)
		singleton = this;
	else
		return;
}

GameMap::~GameMap()
{
	ClearMap();
}

GameMap* GameMap::GetReference()
{
	if (singleton == nullptr)
		return new GameMap();

	return singleton;
}

std::vector<MapTile*>* GameMap::GetMapTiles()
{
	return &MapTiles;
}

void GameMap::AddNewTile(char* tileRead, int posX, int posY, vector<Sprite>* tiles)
{
	int whichTile = (int)(*tileRead - '0');

	if (whichTile == 0 || whichTile >= tiles->size())
		return;

	MapTile* newTile = new MapTile(tiles->at(whichTile), (MapTileType)(whichTile - 1));
	newTile->SetPosition(Vector2(posX * 8. + 20., posY * 8. + 12.));

	//Debug::GetReference()->DebugCollision(foo);

	MapTiles.push_back(newTile);
}

void GameMap::ReadMapLine(string* line, int posY, vector<Sprite>* tiles)
{
	for (int x = 0; x < line->size(); x++)
		AddNewTile(&line->at(x), x, posY, tiles);
}

void GameMap::LoadMap(int world, int level)
{
	vector<string> dataLines;

	ifstream Read ("Levels/" + to_string(world) + to_string(level) + ".txt");

	for (;;)
	{
		string a; 
		Read >> a;

		if (a == "") break;

		dataLines.push_back(a);
	}

	Read.close();

	//vector<Sprite>* tiles = Rendering::GetReference()->GetMapPrefabTiles();

	/*for (int y = 0; y < dataLines.size(); y++)
		ReadMapLine(&dataLines[y], y, tiles);*/
}

void GameMap::ClearMap()
{
	for (size_t i = 0; i < MapTiles.size(); i++)
		delete MapTiles[i];

	MapTiles.clear();
}
