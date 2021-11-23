#pragma once

#include <SpriteObject.h>

using namespace std;

enum class FinalObjectType
{
	None = 0,
	MapTile
};

class CollidableSpriteObject : public SpriteObject
{
public:
	CollidableSpriteObject();
	CollidableSpriteObject(Sprite Sprite);
	CollidableSpriteObject(Sprite Sprite, int layer);

	~CollidableSpriteObject();

	virtual void CheckCollision();
	virtual bool IsStatic();
	virtual bool IsTrigger();

	static vector<CollidableSpriteObject*>* GetAllCollidables();

	void Tick() override;
	void OnPositionChange() override;

	virtual void OnCollision(CollidableSpriteObject* collision);

	void SetCollisionOffset(Vector2 vec);
	void SetCollisionBounds(Vector2 vec);

	virtual FinalObjectType GetFinalObjectType();

	SDL_Rect* GetCollisionRect();
	SDL_Rect* GetLocalCollisionRect();
protected:
	SDL_Rect localCollisionRect, globalCollisionRect;
	bool IsOutOfBounds();
	static vector<CollidableSpriteObject*> allCollidables;
	Vector2 velocity;
private:
	virtual bool CheckGameBounds();

	void Initialize();
	virtual bool CorrectIntersection(CollidableSpriteObject* obj);
	void UpdateGlobalCollisionRect();
};

class StaticCollidable : public CollidableSpriteObject
{
public:
	StaticCollidable();
	StaticCollidable(Sprite Sprite);
	StaticCollidable(Sprite Sprite, int layer);

	~StaticCollidable();

	void CheckCollision() override;
	bool IsStatic() override;
private:
};

class TriggerCollidable : public CollidableSpriteObject
{
public:
	TriggerCollidable();
	TriggerCollidable(Sprite Sprite);
	TriggerCollidable(Sprite Sprite, int layer);

	~TriggerCollidable();

	bool IsTrigger() override;
	void CheckCollision() override;
private:
	bool CorrectIntersection(CollidableSpriteObject* obj) override;
	bool CheckGameBounds() override;
};