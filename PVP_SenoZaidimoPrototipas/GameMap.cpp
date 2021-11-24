#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <Rendering.h>
#include <filesystem>

MapTile::MapTile(MapTileType tileType)
{
	mapTileType = tileType;

	switch (mapTileType)
	{
	case MapTileType::Ground:
		SetSprite(Sprite(0, 67, 16, 16));
		SetLayer(LayerType::MapTiles);
		break;
	case MapTileType::Brick:
		break;
	case MapTileType::Empty:
		break;
	case MapTileType::CoinBlock:
		break;
	default:
		break;
	}
}

MapTile::MapTile(Sprite sprite, MapTileType tileType) : StaticCollidable(sprite, (int)LayerType::MapTiles), mapTileType(tileType)
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

std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void GameMap::ReadMapLine(string* line)
{
	vector<string> data = split(line->c_str(), ' ');

	if (data.size() == 0)
		return;

	if(data[0].size() > 0)
		data[0].pop_back();

	if (data[0] == "BLOCKS")
	{
		if (data.size() <= 2)
			return;

		int posX = stoi(data[1]) + 8;
		int amount = stoi(data[2]);

		for (size_t i = 0; i < amount; i++)
		{
			MapTile* newTile = new MapTile(MapTileType::Ground);
			newTile->SetPosition(Vector2(posX + i * 16, 216));
			MapTiles.push_back(newTile);
		}

		for (size_t i = 0; i < amount; i++)
		{
			MapTile* newTile = new MapTile(MapTileType::Ground);
			newTile->SetPosition(Vector2(posX + i * 16, 232));
			MapTiles.push_back(newTile);
		}
	}
	else
		return;

	//Debug::GetReference()->DebugCollision(foo);
}

void GameMap::LoadMap(int world, int level)
{
	vector<string> dataLines;

	string path = "Lygiai\\" + to_string(world) + to_string(level) + ".txt";

	//string path = to_string(world) + to_string(level) + ".txt";

	ifstream Read (path);

	/*if (!Read.is_open())
	{
		path = "..\\..\\" + path;
		Read = ifstream(path);
	}*/

	bool DEBUG_ISOPEN = Read.is_open();

	while (!Read.eof())
	{
		string a; 
		getline(Read, a);

		if (a == "") break;

		dataLines.push_back(a);
	}

	Read.close();

	for (int y = 0; y < dataLines.size(); y++)
		ReadMapLine(&dataLines[y]);
}

void GameMap::ClearMap()
{
	for (size_t i = 0; i < MapTiles.size(); i++)
		delete MapTiles[i];

	MapTiles.clear();
}
