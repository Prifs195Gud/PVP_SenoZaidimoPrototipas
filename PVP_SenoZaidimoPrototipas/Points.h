#pragma once
#include <Transform.h>
#include <SpriteObject.h>
#include <Collision.h>
class Points : public SpriteObject {

public:
	Points(Vector2 pos, Vector2 pointScale);
	~Points();
	void Tick() override;
	Vector2 GetPosition();
	Vector2 GetPointScale();

private:
	int ticksAfterRemove;
	int trigger_delay, trigger_cooldown;
	int points_height;
	Vector2 positionoffset;
	SpriteObject pointObject;
	Vector2 position;
	Vector2 scale;
	

};