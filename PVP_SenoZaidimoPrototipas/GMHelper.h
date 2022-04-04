#pragma once

#include <vector>

using namespace std;

class VHelper
{
public:
	VHelper();
	VHelper(float x, float y);
	~VHelper();
	float GetX();
	float GetY();
private:
	float x;
	float y;
};

class SHelper
{
public:
	SHelper(VHelper v, float x, float y);
	SHelper();
	~SHelper();
	VHelper GetCoords();
	float GetX();
	float GetY();
private:
	float posX;
	float posY;
	float x;
	float y;
};

class MTHelper
{
public:
	MTHelper();
	~MTHelper();

	void SetSprite(SHelper s);
	void SetPosition(VHelper v);
	SHelper GetSprite();
	VHelper GetPosition();
private:
	VHelper v;
	SHelper s;
};

class GMHelper
{
public:
	GMHelper();
	~GMHelper();

	vector<MTHelper*> GetMapTiles();

	void AddFlag(float posX);
	void AddCastle(float posX);
private:
	vector<MTHelper*> maptiles;
};