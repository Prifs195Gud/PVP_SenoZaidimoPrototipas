#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <Rendering.h>
#include <filesystem>
#include <Goomba.h>
#include <CoinBlock.h>
#include <BrickBlock.h>

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

MapTile::MapTile(MapTileType tileType, LayerType layerType)
{
	mapTileType = tileType;
	SetLayer(layerType);

	if (layerType == LayerType::Background)
		EnableCollision(false);

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
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "PIPE")
	{
		if (data.size() <= 2)
			return;

		int posX = stoi(data[1]);
		int height = stoi(data[2]);

		for (int i = 0; i < height - 1; i++)
		{
			MapTile* newTile = new MapTile(Sprite(0, 115, 16, 16), MapTileType::Empty);
			newTile->SetPosition(Vector2(posX, 200. - i * 16));
			MapTiles.push_back(newTile);
		}
		MapTile* newTile = new MapTile(Sprite(0, 99, 16, 16), MapTileType::Empty);
		newTile->SetPosition(Vector2(posX, 200. - (height - 1) * 16));
		MapTiles.push_back(newTile);

		for (int i = 0; i < height - 1; i++)
		{
			MapTile* newTile = new MapTile(Sprite(16, 115, 16, 16), MapTileType::Empty);
			newTile->SetPosition(Vector2(posX + 16, 200. - i * 16));
			MapTiles.push_back(newTile);
		}
		MapTile* newTile2 = new MapTile(Sprite(16, 99, 16, 16), MapTileType::Empty);
		newTile2->SetPosition(Vector2(posX + 16, 200. - (height - 1) * 16));
		MapTiles.push_back(newTile2);
	}
	else if (data[0] == "BRICKBLOCK")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		BrickBlock* brickblock = new BrickBlock();
		brickblock->SetPosition(Vector2(x, y));
	}
	else if (data[0] == "BUSH")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);
		int length = stoi(data[3]);

		MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile->SetSprite(Sprite(160, 107, 8, 16));
		newTile->SetPosition(Vector2(x - 12, y));
		MapTiles.push_back(newTile);

		for (int i = 0; i < length; i++) {
			MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
			newTile->SetSprite(Sprite(168, 107, 16, 16));
			newTile->SetPosition(Vector2(x + i * 16, y));
			MapTiles.push_back(newTile);
		}

		MapTile* newTile2 = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile2->SetSprite(Sprite(184, 107, 8, 16));
		newTile2->SetPosition(Vector2(x + length * 16 - 4, y));
		MapTiles.push_back(newTile2);
	}
	else if (data[0] == "CLOUD")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);
		int length = stoi(data[3]);

		MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile->SetSprite(Sprite(128, 107, 8, 16));
		newTile->SetPosition(Vector2(x - 12, y));
		MapTiles.push_back(newTile);
		MapTile* newTile2 = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile2->SetSprite(Sprite(128, 123, 8, 8));
		newTile2->SetPosition(Vector2(x - 12, y + 12));
		MapTiles.push_back(newTile2);

		for (int i = 0; i < length; i++) {
			MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
			newTile->SetSprite(Sprite(136, 107, 16, 16));
			newTile->SetPosition(Vector2(x + i * 16, y));
			MapTiles.push_back(newTile);
			MapTile* newTile2 = new MapTile(MapTileType::Empty, LayerType::Background);
			newTile2->SetSprite(Sprite(136, 123, 16, 8));
			newTile2->SetPosition(Vector2(x + i * 16, y + 12));
			MapTiles.push_back(newTile2);
		}

		MapTile* newTile3 = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile3->SetSprite(Sprite(152, 107, 8, 16));
		newTile3->SetPosition(Vector2(x + length * 16 - 4, y));
		MapTiles.push_back(newTile3);
		MapTile* newTile4 = new MapTile(MapTileType::Empty, LayerType::Background);
		newTile4->SetSprite(Sprite(152, 123, 8, 8));
		newTile4->SetPosition(Vector2(x + length * 16 - 4, y + 12));
		MapTiles.push_back(newTile4);
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
