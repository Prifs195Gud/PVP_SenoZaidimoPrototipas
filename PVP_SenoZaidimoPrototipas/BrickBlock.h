#pragma once

#include<GameMap.h>

class BrickBlock : public MapTile
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