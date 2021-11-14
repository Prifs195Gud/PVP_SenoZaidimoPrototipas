#include <Transform.h>

Transform::Transform() : position(Vector2()), scale(Vector2(1,1))
{
	velocity = Vector2();
}

Transform::Transform(Vector2 pos) : position(pos), scale(Vector2(1, 1))
{
	velocity = Vector2();
}

Transform::Transform(Vector2 pos, Vector2 objectScale) : position(pos), scale(objectScale)
{
	velocity = Vector2();
}

Transform::~Transform()
{
}

Vector2 Transform::GetPosition()
{
	return position;
}

void Transform::OnPositionChange()
{
}

void Transform::Tick() // override Tickable
{
	Tickable::Tick();
}

void Transform::Translate(Vector2 vec)
{
	position += vec;

	OnPositionChange();
}

void Transform::SetPosition(Vector2 Position)
{
	position = Position;

	OnPositionChange();
}

void Transform::SetVelocity(Vector2 vel)
{
	velocity = vel;
}

Vector2 Transform::GetVelocity()
{
	return velocity;
}
