#pragma once

#include <SpriteObject.h>
#include <vector>
#include <string>
#include <vector>

using namespace std;

class Text
{
public:
	Text();
	Text(std::string text);
	Text(std::string text, bool active);
	Text(std::string text, Vector2 position);

	~Text();

	void SetText(std::string text);
	void SetOffsetStatic(bool var);

	void SetPosition(Vector2 pos);
	Vector2 GetPosition();

	void Translate(Vector2 pos);

	void Enable(bool var);
	bool IsEnabled();
	string NumberToText(int text);

private:
	bool enabled, offsetStatic;

	string originalText;

	Vector2 position;

	std::vector<SpriteObject*> myLetters;

	void ClearText();
};

