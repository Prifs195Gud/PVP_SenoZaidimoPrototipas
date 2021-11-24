#include <Player.h>
#include <Collision.h>

Player* Player::player = nullptr;

void Player::Initialize()
{
	facingRight = true;
	playerMaxSpeed = 1.5;
	playerAcceleration = 1.0f;

	idleRight = Sprite(1, 50,16,16);
	idleLeft = idleRight;

	vector<Sprite> runRightFrames;

	for (int i = 0; i < 3; i++)
		runRightFrames.push_back(Sprite(18 + i * 17, 50, 16, 16));

	runRight.LoadAnimFrames(runRightFrames);
	runRight.EnableRendering(false);

	SetSprite(idleRight);
	Enable(true);
}

Player::Player()
{
	player = this;
	Initialize();
}

Player::Player(PlayerControllerKeymapping KeyMap)
{
	keymap = KeyMap;
	Initialize();
}

Player::~Player()
{
	if (player == this)
		player = nullptr;
}

void Player::OnPositionChange() // override CollidableSpriteObject
{
	CollidableSpriteObject::OnPositionChange();
	runRight.SetPosition(position);
	runLeft.SetPosition(position);
}

void Player::GoDirection(Vector2 direction)
{
	if (direction.x > 0.1f)
	{
		facingRight = true;
		Vector2 newVelocity = velocity + Vector2::right * playerAcceleration;
		if (newVelocity.x > playerMaxSpeed)
			newVelocity.x = playerMaxSpeed;
		SetVelocity(newVelocity);
	}
	else if (direction.x < -0.1f)
	{
		facingRight = false;
		Vector2 newVelocity = velocity + Vector2::left * playerAcceleration;
		if (newVelocity.x < -playerMaxSpeed)
			newVelocity.x = -playerMaxSpeed;
		SetVelocity(newVelocity);
	}
}

void Player::Jump()
{
}

void Player::Crouch()
{
}

void Player::Fire()
{
}

const float terminalVelocity = 2;
void Player::Tick() // override CollidableSpriteObject
{
	if (velocity.y <= terminalVelocity)
	{
		velocity.y += 0.16;
		if (velocity.y > terminalVelocity)
			velocity.y = terminalVelocity;
	}

	if (GetAsyncKeyState(keymap.up))
		Jump();
	else if (GetAsyncKeyState(keymap.down))
		Crouch();

	if (GetAsyncKeyState(keymap.right))
		GoDirection(Vector2(1, 0));
	else if (GetAsyncKeyState(keymap.left))
		GoDirection(Vector2(-1, 0));
	else
		velocity.x *= 0.8;

	if (GetAsyncKeyState(keymap.fire))
		Fire();

	CollidableSpriteObject::Tick();
}

FinalObjectType Player::GetFinalObjectType()
{
	return FinalObjectType::Player;
}

Player* Player::GetPlayer()
{
	return player;
}
