#include "..\PVP_SenoZaidimoPrototipas\GMHelper.h"

VHelper::~VHelper() {

}

float VHelper::GetX() {
	return x;
}

float VHelper::GetY() {
	return y;
}

VHelper::VHelper(float x, float y) {
	this->x = x;
	this->y = y;
}

SHelper::SHelper(VHelper v, float x, float y) {
	posX = v.GetX();
	posY = v.GetY();
	this->x = x;
	this->y = y;
}

SHelper::SHelper() {
	posX = 0;
	posY = 0;
	this->x = 0;
	this->y = 0;
}

VHelper SHelper::GetCoords() {
	return VHelper(posX, posY);
}

float SHelper::GetX() {
	return x;
}

float SHelper::GetY() {
	return y;
}

SHelper::~SHelper() {

}

MTHelper::MTHelper() {
	s = SHelper();
}

MTHelper::~MTHelper() {

}

void MTHelper::SetPosition(VHelper v) {

}

void MTHelper::SetSprite(SHelper s) {
	this->s = s;
}

SHelper MTHelper::GetSprite() {
	return s;
}

GMHelper::GMHelper() {

}

GMHelper::~GMHelper() {

}

vector<MTHelper*> GMHelper::GetMapTiles() {
	return maptiles;
}

void GMHelper::AddFlag(float posX) {
	MTHelper* topflag = new MTHelper;
	topflag->SetSprite(SHelper(VHelper(257, 8), 20, 89));
	maptiles.push_back(topflag);
	MTHelper* bottomflag = new MTHelper;
	bottomflag->SetSprite(SHelper(VHelper(272, 33), 2, 64));
	maptiles.push_back(bottomflag);
}

void GMHelper::AddCastle(float posX) {
	
}