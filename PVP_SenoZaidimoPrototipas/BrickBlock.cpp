
#include <BrickBlock.h>
#include <Collision.h>
#include <Sprite.h>
#include <Windows.h>

BrickBlock::BrickBlock() : MapTile(Sprite(Vector2(16, 67), 16, 16))
{
	isRemoved = false;
}

BrickBlock::~BrickBlock()
{
}

void BrickBlock::Tick() // override CollidableSpriteObject
{
	if (isRemoved)
		delete this;
}

void BrickBlock::OnCollision(CollidableSpriteObject* collision)
{
	CollidableSpriteObject::OnCollision(collision);

	if (collision == nullptr)
		return;

	Vector2 objToMe = position - collision->GetPosition();
	if (objToMe.VectorAngle(Vector2::down) * Rad2Deg < 90. && collision->GetFinalObjectType() == FinalObjectType::Player)
		Remove();
	else
		return;
}

void BrickBlock::Remove()
{
	if (!isRemoved)
	{
		isRemoved = true;
	}
}