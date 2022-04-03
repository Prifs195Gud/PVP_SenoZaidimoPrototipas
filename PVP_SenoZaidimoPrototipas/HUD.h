#pragma once

#include <Text.h>
#include <Animation.h>
#include <Tick.h>

class PlayerHUD : public Tickable
{
public:
	PlayerHUD();
	~PlayerHUD();

	static PlayerHUD* GetReference();

	void Tick() override;

	int GetScore();
	int GetCoins();
	int GetWorld();
	int GetLevel();
	int GetTime();
private:
	static PlayerHUD* singleton;

	Text scoreText;
	Text scoreValueText;
	int score;

	Animation moneySpriteAnim;
	Text moneyValueText;
	int money;

	Text worldText;
	Text levelValue;
	int world, level;

	Text timeText;
	Text timeValue;
	double time;
};