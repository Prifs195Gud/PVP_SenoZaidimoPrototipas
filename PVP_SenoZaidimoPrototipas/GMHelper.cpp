#include "..\PVP_SenoZaidimoPrototipas\GMHelper.h"

MTHelper::MTHelper() {

}

MTHelper::~MTHelper() {

}

void MTHelper::SetPosition(VHelper v) {

}

void MTHelper::SetSprite(SHelper s) {

}

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
}

SHelper::~SHelper() {

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
	maptiles.push_back(topflag);
	MTHelper* bottomflag = new MTHelper;
	maptiles.push_back(bottomflag);
}

void GMHelper::AddCastle(float posX) {
	
}