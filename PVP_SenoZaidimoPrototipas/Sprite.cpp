#include <Sprite.h>

Sprite::Sprite()
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1;
	rect.h = 1;
	textureData = rect;
}
Sprite::Sprite(SDL_Rect data)
{
	textureData = data;
}
Sprite::Sprite(Vector2 texturePosition, int width, int height)
{
	SDL_Rect rect;
	rect.x = (int)texturePosition.x;
	rect.y = (int)texturePosition.y;
	rect.w = width;
	rect.h = height;
	textureData = rect;
}

Sprite::Sprite(Vector2 texturePosition, Vector2 widthHeight)
{
	SDL_Rect rect;
	rect.x = (int)texturePosition.x;
	rect.y = (int)texturePosition.y;
	rect.w = (int)widthHeight.x;
	rect.h = (int)widthHeight.y;
	textureData = rect;
}

Sprite::~Sprite()
{

}

SDL_Rect* Sprite::GetTextureData()
{
	return &textureData;
}
Vector2 Sprite::GetTexturePosition()
{
	return Vector2(textureData.x, textureData.y);
}
int Sprite::GetTextureWidth()
{
	return textureData.w;
}
int Sprite::GetTextureHeight()
{
	return textureData.h;
}