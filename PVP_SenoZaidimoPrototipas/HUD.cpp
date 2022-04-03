
#include <HUD.h>

PlayerHUD* PlayerHUD::singleton = nullptr;

PlayerHUD::PlayerHUD()
{
	score = 0;
	money = 0;
	world = 1;
	level = 1;
	time = 160;

	scoreText.SetText("mario");
	scoreText.SetPosition(Vector2(28, 12));
	scoreText.SetOffsetStatic(true);

	scoreValueText.SetText("000000");
	scoreValueText.SetPosition(Vector2(28, 20));
	scoreValueText.SetOffsetStatic(true);

	vector<Sprite> animFrames = vector<Sprite>();
	for (int i = 0; i < 3; i++) // 1 2 3
		animFrames.push_back(Sprite(Vector2(97 + i * 5, 83), Vector2(5,8)));
	animFrames.push_back(Sprite(Vector2(102, 83), Vector2(5, 8))); // 2
	moneySpriteAnim.LoadAnimFrames(animFrames);
	moneySpriteAnim.SetPosition(Vector2(90, 20));
	moneySpriteAnim.SetOffsetStatic(true);

	moneyValueText.SetText("x00");
	moneyValueText.SetPosition(Vector2(98, 20));
	moneyValueText.SetOffsetStatic(true);

	worldText.SetText("world");
	worldText.SetPosition(Vector2(147, 12));
	worldText.SetOffsetStatic(true);

	levelValue.SetText("1-1");
	levelValue.SetPosition(Vector2(155, 20));
	levelValue.SetOffsetStatic(true);

	timeText.SetText("time");
	timeText.SetPosition(Vector2(203, 12));
	timeText.SetOffsetStatic(true);

	timeValue.SetText("");
	timeValue.SetPosition(Vector2(203, 20));
	timeValue.SetOffsetStatic(true);
}

PlayerHUD::~PlayerHUD()
{
}

PlayerHUD* PlayerHUD::GetReference()
{
	if (singleton == nullptr)
		singleton = new PlayerHUD();

	return singleton;
}

void PlayerHUD::Tick()
{
	Tickable::Tick();
}

int PlayerHUD::GetScore()
{
	return score;
}

int PlayerHUD::GetCoins()
{
	return money;
}

int PlayerHUD::GetWorld()
{
	return world;
}

int PlayerHUD::GetLevel()
{
	return level;
}

int PlayerHUD::GetTime()
{
	return time;
}
