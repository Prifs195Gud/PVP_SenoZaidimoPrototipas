#pragma once

#include<GameMap.h>

class BrickBlock : public CollidableSpriteObject
{
private:
	bool isRemoved;
public:
	BrickBlock();
	~BrickBlock();

	void OnCollision(CollidableSpriteObject* collision) override;
	void Tick() override;
	void Remove();
};