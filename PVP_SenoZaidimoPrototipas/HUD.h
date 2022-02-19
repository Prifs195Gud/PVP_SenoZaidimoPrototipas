#pragma once

#include <Text.h>
#include <Animation.h>

class PlayerHUD
{
public:
	PlayerHUD();
	~PlayerHUD();

	static PlayerHUD* GetReference();
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
	int time;
};