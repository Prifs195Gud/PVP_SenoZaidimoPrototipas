#include <SpriteObject.h>
#include <Rendering.h>

vector<SpriteObject*> SpriteObject::allObjects = vector<SpriteObject*>();
unordered_map<int, vector<SpriteObject*>> SpriteObject::objectLayers = unordered_map<int, vector<SpriteObject*>>();

void SpriteObject::Initialize(int Layer)
{
	renderData = SDL_Rect();

	renderingEnabled = true;
	markedForDeletion = false;

	scale = Vector2(1, 1);
	position = Vector2(0, 0);

	allObjects.push_back(this);

	layer = Layer;
	objectLayers[layer].push_back(this);

	OnPositionChange();
}

SpriteObject::SpriteObject() : sprite(Sprite())
{
	Initialize(0);
}

SpriteObject::SpriteObject(Sprite Sprite) : sprite(Sprite)
{
	Initialize(0);
}

SpriteObject::SpriteObject(Sprite Sprite, int Layer) : sprite(Sprite)
{
	Initialize(Layer);
}

SpriteObject::~SpriteObject()
{
	allObjects.erase(remove(allObjects.begin(), allObjects.end(), this));
	
	vector<SpriteObject*>* myLayer = &objectLayers[layer];
	myLayer->erase(remove(myLayer->begin(), myLayer->end(), this));
}

vector<SpriteObject*>* SpriteObject::GetAllObjects()
{
	return &allObjects;
}

unordered_map<int, vector<SpriteObject*>>* SpriteObject::GetAllLayers()
{
	return &objectLayers;
}

void SpriteObject::Enable(bool var)
{
	renderingEnabled = var;
}

bool SpriteObject::IsEnabled()
{
	return renderingEnabled;
}

bool SpriteObject::IsMarkedForDeletion()
{
	return markedForDeletion;
}

void SpriteObject::MarkForDeletion()
{
	markedForDeletion = true;
}

SDL_Rect* SpriteObject::GetTextureData()
{
	return sprite.GetTextureData();
}

void SpriteObject::UpdateRenderData(Vector2 worldScale)
{
	renderData.x = (int)((position.x - sprite.GetTextureWidth() * 0.5 * scale.x) * worldScale.x);
	renderData.y = (int)((position.y - sprite.GetTextureHeight() * 0.5 * scale.y) * worldScale.y);

	renderData.w = (int)(sprite.GetTextureWidth() * worldScale.x * scale.x);
	renderData.h = (int)(sprite.GetTextureHeight() * worldScale.y * scale.y);
}

void SpriteObject::OnPositionChange() // override Transform
{
	Transform::Tick();
	UpdateRenderData(Rendering::GetReference()->GetRenderScale());
}

SDL_Rect* SpriteObject::GetRenderData()
{
	return &renderData;
}

void SpriteObject::SetSprite(Sprite SPRITE)
{
	sprite = SPRITE;
	OnPositionChange();
}