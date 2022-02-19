#pragma once

#include <Vectors.h>
#include <Tick.h>

// Tas kas turi tureti informacija apie vieta, skale ir greiti
class Transform : public Tickable
{
public:
	Transform();
	Transform(Vector2 pos);
	Transform(Vector2 pos, Vector2 objectScale);
	~Transform();

	Vector2 GetPosition();

	virtual void OnPositionChange();
	void Tick() override;

	void Translate(Vector2 vec);
	void SetPosition(Vector2 Position);

	void SetVelocity(Vector2 vel);
	Vector2 GetVelocity();
protected:
	Vector2 position, scale, velocity;
};