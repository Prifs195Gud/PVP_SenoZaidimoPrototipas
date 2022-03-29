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

	// Jei pasikeicia pozicija isvestines klases gali nuspresti ka daryti
	virtual void OnPositionChange(); 

	// Del periodinio judejimo
	void Tick() override; 

	// Pajudinti objekta su vektoriumi
	void Translate(Vector2 vec); 

	// Nustatoma nauja objekto pozicija
	void SetPosition(Vector2 Position); 
	Vector2 GetPosition();

	void SetVelocity(Vector2 vel);
	Vector2 GetVelocity();

	void SetScale(Vector2 newScale);
	Vector2 GetScale();
protected:
	Vector2 position, scale, velocity;
};