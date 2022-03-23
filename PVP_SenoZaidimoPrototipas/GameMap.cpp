#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <Rendering.h>
#include <filesystem>
#include <Goomba.h>
#include <CoinBlock.h>

MapTile::MapTile(MapTileType tileType)
{
	mapTileType = tileType;
	SetLayer(LayerType::MapTiles);

	switch (mapTileType)
	{
	case MapTileType::Ground:
		SetSprite(Sprite(0, 67, 16, 16));
		break;
	case MapTileType::HardBlock:
		SetSprite(Sprite(0, 83, 16, 16));
		break;
	case MapTileType::Brick:
		break;
	case MapTileType::CoinBlock:
		break;
	case MapTileType::Empty:
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

FinalObjectType MapTile::GetFinalObjectType() // override StaticCollidable
{
	return FinalObjectType::MapTile;
}

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

		for (int i = 0; i < amount; i++)
		{
			MapTile* newTile = new MapTile(MapTileType::Ground);
			newTile->SetPosition(Vector2(posX + i * 16., 216));
			MapTiles.push_back(newTile);
		}

		for (int i = 0; i < amount; i++)
		{
			MapTile* newTile = new MapTile(MapTileType::Ground);
			newTile->SetPosition(Vector2(posX + i * 16., 232));
			MapTiles.push_back(newTile);
		}
	}
	else if (data[0] == "GOOMBA")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		Goomba* goomba = new Goomba();
		goomba->SetPosition(Vector2(x, y));
	}
	else if (data[0] == "COINBLOCK")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		CoinBlock* coinblock = new CoinBlock();
		coinblock->SetPosition(Vector2(x, y));
	}
	else if (data[0] == "HARDBLOCK")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		MapTile* newTile = new MapTile(MapTileType::HardBlock);
		newTile->SetPosition(Vector2(x, y));
	}
		return;

	//Debug::GetReference()->DebugCollision(foo);
}

void GameMap::LoadMap(int world, int level)
{
	vector<string> dataLines;

	string path = "Lygiai\\" + to_string(world) + to_string(level) + ".txt";

	ifstream Read (path);

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
