#include <Player.h>
#include <Collision.h>
#include <GameCamera.h>

Player* Player::player = nullptr;

void Player::Initialize()
{
	facingRight = true;
	onGround = false;
	jumping = false;

	jumpRemaining = 0;
	jumpExhaustionRate = 0.2f;

	playerMaxSpeed = 3;
	playerAcceleration = 0.4f;

	idleRight = Sprite(1, 50, 16,16);
	idleLeft = Sprite(1, 253, 16, 16);

	jumpRight = Sprite(86, 50, 16, 16);
	jumpLeft = Sprite(86, 253, 16, 16);


	vector<Sprite> runRightFrames;

	for (int i = 0; i < 3; i++)
		runRightFrames.push_back(Sprite(18 + i * 17, 50, 16, 16));

	runRight.LoadAnimFrames(runRightFrames);
	runRight.EnableRendering(false);


	vector<Sprite> runLeftFrames;

	for (int i = 0; i < 3; i++)
		runLeftFrames.push_back(Sprite(18 + i * 17, 253, 16, 16));

	runLeft.LoadAnimFrames(runLeftFrames);
	runLeft.EnableRendering(false);


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
	GameCamera* cam = GameCamera::GetReference();
	Vector2 camPos = cam->GetPosition();
	Vector2 extents = cam->GetCameraBounds() * 0.5;

	if (position.x - 8 < camPos.x - extents.x)
		position.x = camPos.x - extents.x + 8;

	if (position.y > extents.y * 2 + 8)
		position.y = -8;

	CollidableSpriteObject::OnPositionChange();
	runRight.SetPosition(position);
	runLeft.SetPosition(position);
}

void Player::OnCollision(CollidableSpriteObject* collision) // override CollidableSpriteObject
{
	CollidableSpriteObject::OnCollision(collision);

	if (collision == nullptr)
		return;

	FinalObjectType type = collision->GetFinalObjectType();
	Vector2 objToMe;

	switch (type)
	{
	case FinalObjectType::MapTile:

		objToMe = position - collision->GetPosition();
		if (objToMe.VectorAngle(Vector2::down) * Rad2Deg < 50.)
			onGround = true;
		break;

	case FinalObjectType::Player:
		break;

	case FinalObjectType::None:
	default:
		break;
	}
}

void Player::GoDirection(Vector2 direction)
{
	if (direction.x > 0.1f)
	{
		facingRight = true;
		SetSprite(idleRight);
		Vector2 newVelocity = velocity + Vector2::right * playerAcceleration;
		if (newVelocity.x > playerMaxSpeed)
			newVelocity.x = playerMaxSpeed;
		SetVelocity(newVelocity);
	}
	else if (direction.x < -0.1f)
	{
		facingRight = false;
		SetSprite(idleLeft);
		Vector2 newVelocity = velocity + Vector2::left * playerAcceleration;
		if (newVelocity.x < -playerMaxSpeed)
			newVelocity.x = -playerMaxSpeed;
		SetVelocity(newVelocity);
	}
}

void Player::Jump()
{
	if (jumping)
	{
		if (jumpRemaining > jumpExhaustionRate)
		{
			velocity.y -= jumpExhaustionRate;
			jumpRemaining -= jumpExhaustionRate;
		}
		else
		{
			velocity.y -= jumpRemaining;
			jumpRemaining = 0;
			jumping = false;
		}
	}

	if (!onGround)
		return;

	onGround = false;
	jumping = true;
	jumpRemaining = 5;
	velocity.y -= 5;
}

void Player::Crouch()
{
}

void Player::Fire()
{
}

void Player::RunAnimation()
{
	if (abs(velocity.x) < 0.1)
	{
		Enable(true);
		runRight.EnableRendering(false);
		runLeft.EnableRendering(false);

		if (facingRight)
			SetSprite(idleRight);
		else
			SetSprite(idleLeft);
	}
	else
	{
		Enable(false);
		runRight.EnableRendering(facingRight);
		runLeft.EnableRendering(!facingRight);

		Animation* runAnim;

		if (facingRight)
			runAnim = &runRight;
		else
			runAnim = &runLeft;

		double ratio = abs(velocity.x) / (double)playerMaxSpeed;
		ratio = 1 - ratio;
		ratio = ratio * 5.0 + 1.5;

		runAnim->SetAnimSpeed((int)ratio);
	}
}

const float terminalVelocity = 5;
void Player::Tick() // override CollidableSpriteObject
{
	if (GetAsyncKeyState(keymap.up))
		Jump();
	else
		jumping = false;

	if (GetAsyncKeyState(keymap.down))
		Crouch();

	if (GetAsyncKeyState(keymap.right))
		GoDirection(Vector2(1, 0));
	else if (GetAsyncKeyState(keymap.left))
		GoDirection(Vector2(-1, 0));
	else
		velocity.x *= 0.8;

	if (velocity.y <= terminalVelocity)
	{
		velocity.y += 0.3;
		if (velocity.y > terminalVelocity)
			velocity.y = terminalVelocity;
	}

	if(!jumping && onGround)
		RunAnimation();
	else
	{
		Enable(true);
		runRight.EnableRendering(false);
		runLeft.EnableRendering(false);

		if (facingRight)
			SetSprite(jumpRight);
		else
			SetSprite(jumpLeft);
	}

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
