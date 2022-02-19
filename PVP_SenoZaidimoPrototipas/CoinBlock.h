#pragma once

#include<GameMap.h>
#include<Animation.h>

class CoinBlock : public MapTile 
{
public: 
	CoinBlock();
	~CoinBlock();

	void OnCollision(CollidableSpriteObject *collision) override;
	void Tick() override;
	void OnPositionChange() override;

private:
	int money_count, coin_max_up;
	int trigger_delay, trigger_cooldown;

	Animation coinblockAnim;
	SpriteObject coinObject;
	Vector2 positionoffset;
};	