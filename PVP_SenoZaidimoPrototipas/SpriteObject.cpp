#include <SpriteObject.h>
#include <Rendering.h>
#include <algorithm>

vector<SpriteObject*> SpriteObject::allObjects = vector<SpriteObject*>();
map<int, vector<SpriteObject*>> SpriteObject::objectLayers = map<int, vector<SpriteObject*>>();

void SpriteObject::Initialize(int Layer)
{
	renderData = SDL_Rect();

	renderingEnabled = true;
	markedForDeletion = false;
	offsetStatic = false;

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

map<int, vector<SpriteObject*>>* SpriteObject::GetAllLayers()
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

	OnRenderDataChange();
}

void SpriteObject::OnRenderDataChange()
{
}

void SpriteObject::Tick() // override Transform
{
	Transform::Tick();
}

void SpriteObject::OnPositionChange() // override Transform
{
	UpdateRenderData(Rendering::GetReference()->GetRenderScale());
}

SDL_Rect* SpriteObject::GetRenderData()
{
	return &renderData;
}

SDL_Rect SpriteObject::GetRenderDataOffseted(Vector2 offset)
{
	if (offsetStatic)
		return renderData;

	SDL_Rect newRect = SDL_Rect();
	newRect.x = renderData.x - (int)offset.x;
	newRect.y = renderData.y - (int)offset.y;
	newRect.w = renderData.w;
	newRect.h = renderData.h;
	return newRect;
}

void SpriteObject::SetSprite(Sprite SPRITE)
{
	sprite = SPRITE;
	UpdateRenderData(Rendering::GetReference()->GetRenderScale());
}

void SpriteObject::SetLayer(LayerType newLayer)
{
	SetLayer((int)newLayer);
}

void SpriteObject::SetLayer(int newLayer)
{
	vector<SpriteObject*>* myLayer = &objectLayers[layer];
	myLayer->erase(remove(myLayer->begin(), myLayer->end(), this));

	layer = newLayer;
	objectLayers[layer].push_back(this);
}

void SpriteObject::SetOffsetStatic(bool var)
{
	offsetStatic = var;
}

bool SpriteObject::IsOffsetStatic()
{
	return offsetStatic;
}
