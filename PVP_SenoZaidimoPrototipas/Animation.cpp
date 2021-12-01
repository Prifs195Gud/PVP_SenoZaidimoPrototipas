#include <Animation.h>
#include <algorithm>

vector<Animation*> Animation::allAnimations = vector<Animation*>();

void Animation::Initialize()
{
	tickCount = 0;
	currentFrame = 0;

	myShowObject = SpriteObject(Sprite());

	allAnimations.push_back(this);
}

void Animation::SetFrame(int frame)
{
	currentFrame = frame;
	myShowObject.SetSprite(animFrames[frame]);
}

Animation::Animation() : tickMax(10)
{
	Initialize();
}

Animation::Animation(int maxAnimTickCount)
{
	Initialize();

	if (maxAnimTickCount < 0)
		maxAnimTickCount *= -1;

	tickMax = maxAnimTickCount;
}

Animation::~Animation()
{
	allAnimations.erase(remove(allAnimations.begin(), allAnimations.end(), this));
}

void Animation::LoadAnimFrames(Sprite frame)
{
	animFrames.push_back(frame);
	SetFrame(currentFrame);
}

void Animation::LoadAnimFrames(vector<Sprite> frames)
{
	for (size_t i = 0; i < frames.size(); i++)
		LoadAnimFrames(frames[i]);
}

void Animation::Tick() // override Transform
{
	Transform::Tick();

	if (!myShowObject.IsEnabled() || animFrames.size() == 0)
		return;

	tickCount++;

	if (tickCount > tickMax)
	{
		currentFrame++;
		tickCount = 0;

		if (currentFrame >= animFrames.size())
			currentFrame = 0;

		SetFrame(currentFrame);
	}
}

void Animation::SetAnimSpeed(int maxAnimTickCount)
{
	tickMax = abs(maxAnimTickCount);
}

void Animation::EnableRendering(bool var)
{
	myShowObject.Enable(var);
}

vector<Animation*>* Animation::GetAllAnimations()
{
	return &allAnimations;
}

void Animation::OnPositionChange() // override Transform
{
	Transform::OnPositionChange();
	myShowObject.SetPosition(position);
}