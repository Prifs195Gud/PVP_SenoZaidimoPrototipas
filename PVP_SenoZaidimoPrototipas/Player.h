#pragma once

#include <Collision.h>
#include <Windows.h>
#include <Animation.h>

struct PlayerControllerKeymapping
{
	char up = 'W';
	char left = 'A';
	char down = 'S';
	char right = 'D';


	char fire = VK_SPACE;
};

class Player : public CollidableSpriteObject
{
public:
	Player();
	Player(PlayerControllerKeymapping KeyMap);

	~Player();

	void OnPositionChange() override;
	void OnCollision(CollidableSpriteObject* collision) override;
	void Tick() override;
	FinalObjectType GetFinalObjectType() override;

	static Player* GetPlayer();
private:
	bool initialized, onGround, jumping;
	void Initialize();

	void GoDirection(Vector2 direction);
	void Jump();
	void Crouch();
	void Fire();
	void RunAnimation();

	static Player* player;

	PlayerControllerKeymapping keymap;

	float playerMaxSpeed, playerAcceleration;
	float jumpRemaining, jumpExhaustionRate;

	bool facingRight;

	Animation runRight, runLeft;
	Sprite idleRight, idleLeft, jumpRight, jumpLeft;
};