#pragma once
#include <Transform.h>
#include <Animation.h>
#include <SpriteObject.h>
#include <Collision.h>

class Goomba : public CollidableSpriteObject 
{
private:
	Animation walkingAnimation;
	SpriteObject deathTexture;

	float speed;

	bool goingRight;
	bool isRemoved;
	bool activated;

	int ticksAfterRemove;
	int ticksDidntMove, changeDirectionTicksThreshold;

	Vector2 oldPosition;

public:
	Goomba();
	~Goomba();

	void Tick() override;
	void OnPositionChange() override;
	void Remove();
	void CheckDirectionChange();
	FinalObjectType GetFinalObjectType() override;
};