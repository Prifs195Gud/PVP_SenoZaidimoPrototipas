#include <CoinBlock.h>
#include<Collision.h>
#include<Sprite.h>
CoinBlock::CoinBlock():MapTile(Sprite (Vector2(161,67),16,16), MapTileType::CoinBlock)
{ 
 money_count=5;
 trigger_delay=10;
 trigger_cooldown=0;
 Enable(false);
 Sprite a= Sprite(Vector2(113, 67), 16, 16);
 Sprite b= Sprite(Vector2(129, 67), 16, 16);
 Sprite c= Sprite(Vector2(145, 67), 16, 16);

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
	if (trigger_cooldown > 0) 	return;
	money_count--;
	trigger_cooldown = trigger_delay;

}
void CoinBlock::Tick()
{
	CollidableSpriteObject::Tick();
	if (trigger_cooldown > 0) 	trigger_cooldown--;
	
}

void CoinBlock::OnPositionChange()
{
	coinblockAnim.SetPosition(position);
	CollidableSpriteObject::OnPositionChange();
	
}

