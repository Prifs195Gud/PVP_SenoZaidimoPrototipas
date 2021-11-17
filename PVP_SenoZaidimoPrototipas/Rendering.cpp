#include <Rendering.h>
#include <list>
#include <string>
#include <unordered_map>

Rendering* Rendering::singleton = nullptr;

void Rendering::DrawMapBackground()
{
	SDL_SetRenderDrawColor(mainRenderer, 92, 148, 252, 255);
	SDL_RenderDrawRect(mainRenderer, NULL);
}

void Rendering::RenderAllObjects()
{
	unordered_map<int, vector<SpriteObject*>>* layers = SpriteObject::GetAllLayers();
	unordered_map<int, vector<SpriteObject*>>::iterator it = layers->begin();

	while (it != layers->end())
	{
		vector<SpriteObject*> layer = (*it).second;

		for (size_t i = 0; i < layer.size(); i++)
		{
			SpriteObject* object = layer[i];
			if (object->IsEnabled())
				SDL_RenderCopy(mainRenderer, tileset, object->GetTextureData(), object->GetRenderData());
		}

		it++;
	}
}

void Rendering::RenderWindow()
{
	SDL_RenderClear(mainRenderer);

	DrawMapBackground();
	RenderAllObjects();

	SDL_RenderPresent(mainRenderer);
}

Rendering::Rendering()
{
	if (singleton == nullptr)
	{
		singleton = this;
		InitializeMapTiles();
		InitializeFont();
	}

	mainRenderer = nullptr;
	tileset = nullptr;
}

void Rendering::InitializeFont()
{
	std::string charSet = "0123456789abcdefghijklmnopqrstuvwxyz-";

	Vector2 letterPositions[37];

	for (int i = 0; i < 37; i++) // 0123456789
		letterPositions[i] = Vector2(i * 8, 0);

	Vector2 letterSize = Vector2(8, 8);

	for (size_t i = 0; i < 37; i++)
	{
		lettersData.push_back(Sprite(letterPositions[i], letterSize));
		lettersHashmap[charSet[i]] = i;
	}
}

void Rendering::InitializeMapTiles()
{
}

Rendering::~Rendering()
{
}

Rendering* Rendering::GetReference()
{
	if (singleton == nullptr)
		return new Rendering();

	return singleton;
}

Vector2 Rendering::GetRenderScale()
{
	return renderScale;
}

void Rendering::SetTileset(SDL_Texture* tileset_)
{
	tileset = tileset_;
}

void Rendering::SetRenderer(SDL_Renderer* renderer)
{
	mainRenderer = renderer;
}

SDL_Renderer* Rendering::GetRenderer()
{
	return mainRenderer;
}

std::vector<Sprite>* Rendering::GetLetterTextures()
{
	return &lettersData;
}

Sprite Rendering::GetLetterTexture(char letter)
{
	if (!lettersHashmap.count(letter))
		return Sprite();

	return lettersData[lettersHashmap[letter]];
}