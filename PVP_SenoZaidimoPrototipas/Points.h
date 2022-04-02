#pragma once
#include <Transform.h>
#include <SpriteObject.h>
#include <Collision.h>
class Points : public SpriteObject {

public:
	Points(Vector2 pos);
	~Points();
	void Tick() override;
	//void OnPositionChange() override;

private:
	int ticksAfterRemove;
	int trigger_delay, trigger_cooldown;
	int points_height;
	Vector2 positionoffset;
	SpriteObject pointObject;
	Vector2 position;

};