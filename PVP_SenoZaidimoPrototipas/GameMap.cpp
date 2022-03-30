#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <Rendering.h>
#include <filesystem>
#include <Goomba.h>
#include <CoinBlock.h>
#include <BrickBlock.h>

MapTile::MapTile(Sprite sprite) : StaticCollidable(sprite, (int)LayerType::MapTiles)
{
}

MapTile::MapTile(Sprite sprite, LayerType layerType) : StaticCollidable(sprite, (int)layerType)
{
	if (layerType == LayerType::Background)
		EnableCollision(false);
}

MapTile::~MapTile()
{
}

FinalObjectType MapTile::GetFinalObjectType() // override StaticCollidable
{
	return FinalObjectType::MapTile;
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

Sprite bushes[3] = { Sprite(Vector2(160, 107), 32, 16) ,Sprite(Vector2(192, 107), 48, 16),  Sprite(Vector2(160, 91), 64, 16) };
Sprite clouds[3] = { Sprite(Vector2(128, 107), 32, 24) ,Sprite(Vector2(80, 107), 48, 24),  Sprite(Vector2(186, 219), 64, 24) };

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
			MapTile* newTile = new MapTile(Sprite(0, 67, 16, 16));
			newTile->SetPosition(Vector2(posX + i * 16., 216));
			MapTiles.push_back(newTile);
		}

		for (int i = 0; i < amount; i++)
		{
			MapTile* newTile = new MapTile(Sprite(0, 67, 16, 16));
			newTile->SetPosition(Vector2(posX + i * 16., 232));
			MapTiles.push_back(newTile);
		}
	}
	else if (data[0] == "GOOMBA")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]) + 8;
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
		MapTiles.push_back(coinblock);
	}
	else if (data[0] == "HARDBLOCK")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		MapTile* newTile = new MapTile(Sprite(0, 83, 16, 16));
		newTile->SetPosition(Vector2(x, y));
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "BRICKBLOCK")
	{
		if (data.size() <= 2)
			return;

		float x = stof(data[1]);
		float y = stof(data[2]);

		BrickBlock* brickblock = new BrickBlock();
		brickblock->SetPosition(Vector2(x, y));
		MapTiles.push_back(brickblock);
	}
	else if (data[0] == "PIPE")
	{
		if (data.size() <= 2)
			return;

		int posX = stoi(data[1]) + 16;
		int height = stoi(data[2]);

		if (height < 2 || height > 4)
			return;

		MapTile* newTile = new MapTile(Sprite(Vector2(154, 219), 32, height * 16));
		newTile->SetPosition(Vector2(posX, 208 - height * 8.));
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "BUSH")
	{
		if (data.size() <= 2)
			return;

		int posX = stoi(data[1]);
		int length = stoi(data[2]);

		if (length < 1 || length > 3)
			return;

		MapTile* newTile = new MapTile(bushes[length - 1], LayerType::Background);
		newTile->SetPosition(Vector2(posX + (length + 2) * 8., 200));
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "CLOUD")
	{
		if (data.size() <= 3)
			return;

		int posX = stoi(data[1]);
		int posY = stoi(data[2]);
		int length = stoi(data[3]);

		if (length < 1 || length > 3)
			return;

		MapTile* newTile = new MapTile(clouds[length - 1], LayerType::Background);
		newTile->SetPosition(Vector2(posX + (length + 2) * 8., posY - 8.));
		MapTiles.push_back(newTile);
	}
	else if (data[0] == "MOUNTAIN")
	{
		if (data.size() <= 2)
			return;

		int posX = stoi(data[1]);
		int width = stoi(data[2]);

		if (width != 3 && width != 5)
			return;

		MapTile* newTile = new MapTile(Sprite(Vector2(154, 32), 80, 35), LayerType::Background);

		newTile->SetPosition(Vector2(posX + 24., 208. - 1.5));
		if (width == 5)
			newTile->SetPosition(Vector2(posX + 40., 208. - 17.5));

		MapTiles.push_back(newTile);
	}
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
