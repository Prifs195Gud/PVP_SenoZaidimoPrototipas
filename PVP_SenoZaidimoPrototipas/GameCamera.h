#pragma once

#include <Transform.h>
#include <SpriteObject.h>
#include <Vectors.h>

class GameCamera : public Transform
{
public:
	static GameCamera* GetReference();

	bool IsPointInView(Vector2 point);
	bool IsObjectInView(SpriteObject* trans);

	void Tick() override;

	Vector2 GetCameraBounds();
private:
	static GameCamera* singleton;

	int camWidth, camHeight;

	Vector2 defaultPos;

	GameCamera();
	~GameCamera();
};