
#include <CoinBlock.h>
#include <Collision.h>
#include <Sprite.h>
#include <Windows.h>

CoinBlock::CoinBlock() :MapTile(Sprite(Vector2(161, 67), 16, 16), MapTileType::CoinBlock), coinObject(Sprite(), -1)
{
	coinObject.SetSprite(Sprite(Vector2(116, 85), 10, 14));

	coin_max_up = 32;
	money_count = 5;
	trigger_delay = 16;
	trigger_cooldown = 0;

	Enable(false);

	Sprite a = Sprite(Vector2(113, 67), 16, 16);
	Sprite b = Sprite(Vector2(129, 67), 16, 16);
	Sprite c = Sprite(Vector2(145, 67), 16, 16);

	coinblockAnim.LoadAnimFrames(a);
	coinblockAnim.LoadAnimFrames(b);
	coinblockAnim.LoadAnimFrames(c);
	coinblockAnim.LoadAnimFrames(b);
}

CoinBlock::~CoinBlock()
{
}

void CoinBlock::OnCollision(CollidableSpriteObject* collision)
{
	CollidableSpriteObject::OnCollision(collision);

	if (collision == nullptr)
		return;

	Vector2 objToMe = position - collision->GetPosition();
	if (!(objToMe.VectorAngle(Vector2::down) * Rad2Deg < 90.))
		return;

	if (trigger_cooldown > 0 || money_count <= 0)
		return;

	money_count--;
	trigger_cooldown = trigger_delay;

	if (money_count <= 0)
	{
		Enable(true);
		coinblockAnim.EnableRendering(false);
	}
}
void CoinBlock::Tick()
{
	CollidableSpriteObject::Tick();
	
	if (trigger_cooldown > 0) 
	{
		coinObject.Enable(true);

		float ratio = trigger_cooldown /(float)trigger_delay;
		ratio = 1 - ratio;

		positionoffset.y = -sin(ratio * 3.14) * coin_max_up;

		coinObject.SetPosition(position + positionoffset);
		trigger_cooldown--;
	}
	else 
		coinObject.Enable(false);
}

void CoinBlock::OnPositionChange()
{
	CollidableSpriteObject::OnPositionChange();

	coinblockAnim.SetPosition(position);
	coinObject.SetPosition(position + positionoffset);
}

