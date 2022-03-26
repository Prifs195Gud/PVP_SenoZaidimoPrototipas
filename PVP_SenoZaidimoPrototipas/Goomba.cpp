#include <Goomba.h>
#include <GameCamera.h>
#include <Game.h>

Goomba::Goomba() : CollidableSpriteObject(Sprite(Vector2(32, 131), 16, 16))
{
	deathTexture.SetSprite(Sprite(Vector2(32, 131), 16, 16));
	deathTexture.Enable(false);

	walkingAnimation.LoadAnimFrames(Sprite(Vector2(0, 131), 16, 16));
	walkingAnimation.LoadAnimFrames(Sprite(Vector2(16, 131), 16, 16));

	isRemoved = false;
	activated = false;
	goingRight = false;

	speed = 0.5f;
	ticksAfterRemove = 0;
	ticksDidntMove = 0;
	changeDirectionTicksThreshold = 2;

	Enable(false);
}

Goomba::~Goomba()
{

}

void Goomba::CheckDirectionChange()
{
	if (oldPosition == position)
		ticksDidntMove++;
	else
		ticksDidntMove = 0;

	if (ticksDidntMove >= changeDirectionTicksThreshold)
	{
		ticksDidntMove = 0;
		goingRight = !goingRight;
	}

	oldPosition = position;
}

void Goomba::Tick() // override CollidableSpriteObject
{
	if (isRemoved) 
	{
		SetVelocity(Vector2::zero);

		if (ticksAfterRemove < 100)
			ticksAfterRemove++;
		else 
			delete this;
	}
	else
	{
		if (!activated)
		{
			if(abs(position.x - GameCamera::GetReference()->GetPosition().x) < GAME_BASE_RESOLUTION.x / 2)
				activated = true;

			return;
		}

		Vector2 vel = velocity;

		CheckDirectionChange();

		if (goingRight)
			vel.x = speed;
		else
			vel.x = -speed;

		if(vel.y < 5)
			vel.y += 0.3;

		SetVelocity(vel);
		CollidableSpriteObject::Tick();
	}
}

void Goomba::OnPositionChange() // override CollidableSpriteObject
{
	CollidableSpriteObject::OnPositionChange();

	deathTexture.SetPosition(position);
	walkingAnimation.SetPosition(position);
}

void Goomba::Remove()
{
	if (!isRemoved) 
	{
		isRemoved = true;
		walkingAnimation.EnableRendering(false);
		deathTexture.Enable(true);
		EnableCollision(false);
	}
}

FinalObjectType Goomba::GetFinalObjectType() // override CollidableSpriteObject
{
	return FinalObjectType::Enemy;
}
