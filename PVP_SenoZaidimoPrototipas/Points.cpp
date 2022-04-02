#include<Points.h>

Points::Points(Vector2 pos) : SpriteObject(Sprite(Vector2(0, 280), 21, 7)) {

	position = pos;
	points_height = 50;
	trigger_cooldown = 0;
	trigger_delay = 16;
	ticksAfterRemove = 0;
	//SetSprite(Sprite(Vector2(0, 280), 21, 7));
	Enable(true);
	SetPosition(position + positionoffset);
	//SetSprite(Sprite(Vector2(0, 280), 21, 7));
	//pointObject.Enable(true);
	//pointObject.SetPosition(position);
}

Points::~Points() {

}
void Points::Tick() {

	SpriteObject::Tick();

	if (trigger_cooldown >= 8) {
		float ratio = trigger_cooldown / (float)trigger_delay;
		ratio = 1 - ratio;

		positionoffset.y = -sin(ratio * 3.14) * points_height;
		trigger_cooldown--;
	}
	SetPosition(position +positionoffset );


	if (ticksAfterRemove < 200)
		ticksAfterRemove++;
	else
		delete this;

}

/*
void Points::OnPositionChange() {
	
	SpriteObject::OnPositionChange();

	SetPosition(position );

}
*/

