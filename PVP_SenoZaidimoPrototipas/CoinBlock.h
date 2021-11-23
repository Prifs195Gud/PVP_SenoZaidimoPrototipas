#pragma once
#include<GameMap.h>
#include<Animation.h>
class CoinBlock : public MapTile {
public: 
	CoinBlock();
	~CoinBlock();
	void OnCollision(CollidableSpriteObject *collision) override;
	void Tick() override;
	void OnPositionChange() override;

private:
	int money_count;
	int trigger_delay;
	int trigger_cooldown;
	Animation coinblockAnim;


};	