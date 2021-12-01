#pragma once

#include <Transform.h>
#include <Sprite.h>
#include <SpriteObject.h>
#include <vector>

using namespace std;

class Animation : public Transform
{
public:
	Animation();
	Animation(int maxAnimTickCount);
	~Animation();

	void LoadAnimFrames(Sprite frame);
	void LoadAnimFrames(vector<Sprite> frames);

	void Tick() override;

	void SetAnimSpeed(int maxAnimTickCount);
	void SetOffsetStatic(bool var);

	void EnableRendering(bool var);

	static vector<Animation*>* GetAllAnimations();

	void OnPositionChange() override;
private:
	static vector<Animation*> allAnimations;

	int tickCount, tickMax, currentFrame;
	vector<Sprite> animFrames;
	SpriteObject myShowObject;

	void Initialize();
	void SetFrame(int frame);
};