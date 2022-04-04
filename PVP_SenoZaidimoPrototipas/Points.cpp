#include<Points.h>

Points::Points(Vector2 pos, Vector2 scale1) : SpriteObject(Sprite(Vector2(0, 280), 21, 7)) {

	position = pos;
	points_height = 50;
	trigger_cooldown = 16;
	trigger_delay = 16;
	ticksAfterRemove = 0;
	SetScale(scale1);
	Enable(true);
	SetPosition(position + positionoffset);
	
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


	if (ticksAfterRemove < 100)
		ticksAfterRemove++;
	else
		delete this;

}
Vector2 Points::GetPosition() {
	return position; 
}



