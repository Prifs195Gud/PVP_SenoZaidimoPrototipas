#pragma once
#include <Transform.h>
#include <Animation.h>
#include <SpriteObject.h>
#include <Collision.h>

class Goomba : public CollidableSpriteObject 
{
private:

	Vector2 positionoffset;
	Animation walkingAnimation;
	SpriteObject deathTexture;
	float speed;
	bool goingRight;
	bool isRemoved;
	int ticksAfterRemove;

public:
	Goomba();
	~Goomba();

	void OnCollision(CollidableSpriteObject* collision) override;
	void Tick() override;
	void OnPositionChange() override;
	void Remove();
	FinalObjectType GetFinalObjectType() override;
};