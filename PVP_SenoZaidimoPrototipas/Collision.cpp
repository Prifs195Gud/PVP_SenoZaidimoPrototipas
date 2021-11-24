
#include <Collision.h>

vector<CollidableSpriteObject*> CollidableSpriteObject::allCollidables = vector<CollidableSpriteObject*>();

bool CollidableSpriteObject::CheckGameBounds()
{
	if (IsOutOfBounds())
	{
		OnCollision(nullptr);
		Translate(-velocity);

		return true;
	}

	return false;
}

bool CollidableSpriteObject::IsOutOfBounds()
{
	SDL_Rect* myTexture = GetTextureData();
	return position.x - myTexture->w / 2. <= 15
		|| position.x + myTexture->w / 2. >= 226
		|| position.y - myTexture->h / 2. <= 7
		|| position.y + myTexture->h / 2. >= 218;
}

FinalObjectType CollidableSpriteObject::GetFinalObjectType()
{
	return FinalObjectType::Player;
}

void CollidableSpriteObject::Initialize()
{
	allCollidables.push_back(this);

	localCollisionRect = *sprite.GetTextureData();
	localCollisionRect.x = 0;
	localCollisionRect.y = 0;

	velocity = Vector2::zero;

	UpdateGlobalCollisionRect();
}

CollidableSpriteObject::CollidableSpriteObject() : SpriteObject()
{
	Initialize();
}

CollidableSpriteObject::CollidableSpriteObject(Sprite Sprite) : SpriteObject(Sprite)
{
	Initialize();
}

CollidableSpriteObject::CollidableSpriteObject(Sprite Sprite, int layer) : SpriteObject(Sprite, layer)
{
	Initialize();
}

CollidableSpriteObject::~CollidableSpriteObject()
{
	allCollidables.erase(remove(allCollidables.begin(), allCollidables.end(), this));
}

void CollidableSpriteObject::CheckCollision(CollidableSpriteObject* objectOfInterest)
{
	if (!IsEnabled() || !objectOfInterest->IsEnabled())
		return;

	CorrectIntersection(objectOfInterest);
}

bool CollidableSpriteObject::IsStatic()
{
	return false;
}

bool CollidableSpriteObject::IsTrigger()
{
	return false;
}

vector<CollidableSpriteObject*>* CollidableSpriteObject::GetAllCollidables()
{
	return &allCollidables;
}

void CollidableSpriteObject::UpdateGlobalCollisionRect()
{
	globalCollisionRect = localCollisionRect;

	globalCollisionRect.w *= (int)scale.x;
	globalCollisionRect.h *= (int)scale.y;

	globalCollisionRect.x += (int)position.x;
	globalCollisionRect.y += (int)position.y;
}

void CollidableSpriteObject::OnPositionChange() // override SpriteObject
{
	SpriteObject::OnPositionChange();
	UpdateGlobalCollisionRect();
}

void CollidableSpriteObject::OnRenderDataChange() // override SpriteObject
{
	SpriteObject::OnRenderDataChange();

	localCollisionRect = *sprite.GetTextureData();
	localCollisionRect.x = 0;
	localCollisionRect.y = 0;
	UpdateGlobalCollisionRect();
}

void CollidableSpriteObject::Tick() // override SpriteObject
{
	SpriteObject::Tick();
}

void CollidableSpriteObject::OnCollision(CollidableSpriteObject* collision)
{
}

void CollidableSpriteObject::SetCollisionOffset(Vector2 vec)
{
	localCollisionRect.x = (int)vec.x;
	localCollisionRect.y = (int)vec.y;
	UpdateGlobalCollisionRect();
}

void CollidableSpriteObject::SetCollisionBounds(Vector2 vec)
{
	localCollisionRect.w = (int)vec.x;
	localCollisionRect.h = (int)vec.y;
	UpdateGlobalCollisionRect();
}

SDL_Rect* CollidableSpriteObject::GetCollisionRect()
{
	return &globalCollisionRect;
}

SDL_Rect* CollidableSpriteObject::GetLocalCollisionRect()
{
	return &localCollisionRect;
}

bool HasIntersection(SDL_Rect* a, SDL_Rect* b)
{
	return (abs(a->x - b->x) * 2 < (a->w + b->w)) &&
		(abs(a->y - b->y) * 2 < (a->h + b->h));
}

bool CollidableSpriteObject::CorrectIntersection(CollidableSpriteObject* obj)
{
	if (this == obj || !HasIntersection(&globalCollisionRect, obj->GetCollisionRect()))
		return false;

	OnCollision(obj);

	if (obj->IsTrigger())
	{
		obj->OnCollision(this);
		return true;
	}

	obj->OnCollision(this);

	if (obj->IsStatic())
	{
		Vector2 objToMe = position -obj->GetPosition();
		if (objToMe.VectorAngle(Vector2::down) * Rad2Deg < 50.)
		{
			Translate(Vector2(0, -velocity.y));
			velocity.y = 0;
		}
		else
		{
			Translate(Vector2(-velocity.x, 0));
			velocity.x = 0;
		}
	}
	else
	{
		Vector2 meToObj = obj->GetPosition() - position;
		if (meToObj.VectorAngle(velocity) * Rad2Deg < 45.)
		{
			Translate(-velocity);
			velocity = Vector2::zero;
		}

		Vector2 objToMe = -meToObj;
		if (objToMe.VectorAngle(obj->GetVelocity()) * Rad2Deg < 45.)
		{
			obj->Translate(-obj->GetVelocity());
			obj->SetVelocity(Vector2::zero);
		}
	}

	return true;
}

// ***********************************************

StaticCollidable::StaticCollidable() : CollidableSpriteObject()
{
}

StaticCollidable::StaticCollidable(Sprite Sprite) : CollidableSpriteObject(Sprite)
{
}

StaticCollidable::StaticCollidable(Sprite Sprite, int layer) : CollidableSpriteObject(Sprite, layer)
{
}

StaticCollidable::~StaticCollidable()
{
}

void StaticCollidable::CheckCollision(CollidableSpriteObject* objectOfInterest) // override CollidableSpriteObject
{
}

bool StaticCollidable::IsStatic()
{
	return true;
}

// ************************************************

bool TriggerCollidable::IsTrigger()
{
	return true;
}

TriggerCollidable::TriggerCollidable()
{
}

TriggerCollidable::TriggerCollidable(Sprite Sprite)
{
}

TriggerCollidable::TriggerCollidable(Sprite Sprite, int layer)
{
}

TriggerCollidable::~TriggerCollidable()
{
}

void TriggerCollidable::CheckCollision(CollidableSpriteObject* objectOfInterest) // override CollidableSpriteObject
{
	bool collided;
	CollidableSpriteObject* lastCollision = nullptr;

	collided = CheckGameBounds();

	for (size_t i = 0; i < allCollidables.size(); i++)
		if (CorrectIntersection(allCollidables[i]))
		{
			collided = true;
			lastCollision = allCollidables[i];
		}

	if (collided)
		OnCollision(lastCollision);
}

bool TriggerCollidable::CorrectIntersection(CollidableSpriteObject* obj) // override CollidableSpriteObject
{
	if (this == obj || !HasIntersection(&globalCollisionRect, obj->GetCollisionRect()))
		return false;

	obj->OnCollision(this);

	return true;
}

bool TriggerCollidable::CheckGameBounds() // override CollidableSpriteObject
{
	return IsOutOfBounds();
}
