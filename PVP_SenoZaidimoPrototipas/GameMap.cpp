#include "..\PVP_SenoZaidimoPrototipas\GameMap.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <Rendering.h>
#include <filesystem>
#include <Goomba.h>
#include <CoinBlock.h>
#include <BrickBlock.h>
#include <string>

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

		float posX = stof(data[1]) + 8;
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

		float posX = stof(data[1]) + 8;
		float posY = stof(data[2]) - 7;

		Goomba* goomba = new Goomba();
		goomba->SetPosition(Vector2(posX, posY));
	}
	else if (data[0] == "COINBLOCK")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]) + 8;
		float posY = stof(data[2]) - 8;

		CoinBlock* coinblock = new CoinBlock();
		coinblock->SetPosition(Vector2(posX, posY));
		MapTiles.push_back(coinblock);
	}
	else if (data[0] == "HARDBLOCK")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]) + 8;
		float posY = stof(data[2]) - 8;

		MapTile* newTile = new MapTile(MapTileType::HardBlock);
		newTile->SetPosition(Vector2(posX, posY));
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "BRICKBLOCK")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]) + 8;
		float posY = stof(data[2]) - 8;

		BrickBlock* brickblock = new BrickBlock();
		brickblock->SetPosition(Vector2(posX, posY));
		MapTiles.push_back(brickblock);
	}
	else if (data[0] == "PIPE")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]) + 16;
		int height = stoi(data[2]);

		if (height == 2 || height == 3 || height == 4) {
			MapTile* newTile = new MapTile(MapTileType::Empty);
			newTile->SetSprite(Sprite(Vector2(154, 219), 32, height * 16));
			newTile->SetPosition(Vector2(posX, 208 - height * 8.));
			MapTiles.push_back(newTile);

		}
		else {
			return;
		}
	}
	else if (data[0] == "BUSH")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]);
		int length = stoi(data[2]);

		if (length == 1 || length == 2 || length == 3) {
			MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
			if (length == 1) {
				newTile->SetSprite(Sprite(Vector2(160, 107), 32, 16));
			}
			else if (length == 2) {
				newTile->SetSprite(Sprite(Vector2(192, 107), 48, 16));
			}
			else {
				newTile->SetSprite(Sprite(Vector2(160, 91), 64, 16));
			}
			newTile->SetPosition(Vector2(posX + (length + 2) * 8., 200));
			MapTiles.push_back(newTile);
		}
		else {
			return;
		}
	}
	else if (data[0] == "CLOUD")
	{
		if (data.size() <= 3)
			return;

		float posX = stof(data[1]);
		float posY = stof(data[2]);
		int length = stoi(data[3]);

		if (length == 1 || length == 2 || length == 3) {
			MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
			if (length == 1) {
				newTile->SetSprite(Sprite(Vector2(128, 107), 32, 24));
			}
			else if (length == 2) {
				newTile->SetSprite(Sprite(Vector2(80, 107), 48, 24));
			}
			else {
				newTile->SetSprite(Sprite(Vector2(186, 219), 64, 24));
			}
			newTile->SetPosition(Vector2(posX + (length + 2) * 8., posY - 8.));
			MapTiles.push_back(newTile);
		}
		else {
			return;
		}
	}
	else if (data[0] == "MOUNTAIN")
	{
		if (data.size() <= 2)
			return;

		float posX = stof(data[1]);
		int width = stoi(data[2]);

		if (width == 3 || width == 5) {
			MapTile* newTile = new MapTile(MapTileType::Empty, LayerType::Background);
			newTile->SetSprite(Sprite(Vector2(186, 243), 80, 35));
			if (width == 3) {
				newTile->SetPosition(Vector2(posX + 24., 208. - 1.5));
			}
			else {
				newTile->SetPosition(Vector2(posX + 40., 208. - 17.5));
			}
			MapTiles.push_back(newTile);
		}
		else {
			return;
		}
	}
	else if (data[0] == "FLAG") 
	{
		if (data.size() < 1)
			return;

		float posX = stof(data[1]);

		AddFlag(posX);
	}
	else if (data[0] == "CASTLE")
	{
		if (data.size() < 1)
			return;

		float posX = stof(data[1]);

		AddCastle(posX);
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

void GameMap::AddFlag(float posX) {
	MapTile* topflag = new MapTile(MapTileType::Empty, LayerType::Background);
	topflag->SetSprite(Sprite(Vector2(257, 8), 20, 89));
	MapTiles.push_back(topflag);
	MapTile* bottomflag = new MapTile(MapTileType::Empty, LayerType::Background);
	bottomflag->SetSprite(Sprite(Vector2(272, 33), 2, 64));
	MapTiles.push_back(bottomflag);
}

void GameMap::AddCastle(float posX) {
	
}
