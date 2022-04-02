#include <Goomba.h>
#include <HUD.h>
#include <Points.h>
Goomba::Goomba() : CollidableSpriteObject(Sprite(Vector2(32, 131), 16, 16)), pointObject(Sprite(), -1)
{
	points_height = 50;
	trigger_cooldown = 0;
	trigger_delay = 16;
	speed = 0.5f;
	goingRight = false;
 	//pointObject.SetSprite(Sprite(Vector2(0, 280), 21, 7));
	deathTexture.SetSprite(Sprite(Vector2(32, 131), 16, 16));
	walkingAnimation.LoadAnimFrames(Sprite(Vector2(0, 131), 16, 16));
	walkingAnimation.LoadAnimFrames(Sprite(Vector2(16, 131), 16, 16));
	deathTexture.Enable(false);
	//pointObject.Enable(false);
	isRemoved = false;
	ticksAfterRemove = 0;
	//offset.y = 20;
	Enable(false);
}

Goomba::~Goomba()
{
	
}

void Goomba::OnCollision(CollidableSpriteObject* collision) // override CollidableSpriteObject
{
	CollidableSpriteObject::OnCollision(collision);

	if (collision == nullptr)
		return;

	FinalObjectType type = collision->GetFinalObjectType();
	Vector2 objToMe;

	switch (type)
	{
	case FinalObjectType::MapTile:
	case FinalObjectType::Player:
	case FinalObjectType::Enemy:

		if (goingRight)
		{
			objToMe = position - collision->GetPosition();
			if (objToMe.VectorAngle(Vector2::left) * Rad2Deg < 30.)
				goingRight = false;
		}
		else
		{
			objToMe = position - collision->GetPosition();
			if (objToMe.VectorAngle(Vector2::right) * Rad2Deg < 30.)
				goingRight = true;
		}

		break;

	case FinalObjectType::None:
	default:
		break;
	}
}

void Goomba::Tick() // override CollidableSpriteObject
{
	if (isRemoved) 
	{
		SetVelocity(Vector2::zero);
		
		/*
		if (trigger_cooldown >= 8) {
			float ratio = trigger_cooldown / (float)trigger_delay;
			ratio = 1 - ratio;

			positionoffset.y = -sin(ratio * 3.14) * points_height;

			
			trigger_cooldown--;
		}
		pointObject.SetPosition(position + positionoffset);
		*/
		if (ticksAfterRemove < 100)
			ticksAfterRemove++;
		else 
			delete this;
	}
	else
	{
		Vector2 vel = velocity;

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
	//pointObject.SetPosition(position + positionoffset);
}

void Goomba::Remove()
{
	if (!isRemoved) 
	{
		Points *points = new Points(position);
		
		PlayerHUD* playerhud = PlayerHUD::GetReference();
		playerhud->SetScore(100);
		playerhud->DrawScore();
		
		

		trigger_cooldown = trigger_delay;
		isRemoved = true;
		walkingAnimation.EnableRendering(false);
		//pointObject.Enable(true);
		//pointObject.SetPosition(position + positionoffset);
		deathTexture.Enable(true);
		EnableCollision(false);
	}
}

FinalObjectType Goomba::GetFinalObjectType() // override CollidableSpriteObject
{
	return FinalObjectType::Enemy;
}
