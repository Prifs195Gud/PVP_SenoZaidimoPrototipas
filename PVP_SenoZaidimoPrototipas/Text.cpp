#include <Text.h>
#include <Rendering.h>
#include <SpriteObject.h>

Text::Text() :position(Vector2()), enabled(true)
{
	originalText = "";
	offsetStatic = false;
}

Text::Text(std::string text) :position(Vector2()), enabled(true)
{
	offsetStatic = false;
	SetText(text);
}

Text::Text(std::string text, bool active) : position(Vector2()), enabled(true)
{
	offsetStatic = false;
	SetText(text);
	Enable(active);
}

Text::Text(std::string text, Vector2 position) :position(position), enabled(true)
{
	offsetStatic = false;
	SetText(text);
}

Text::~Text()
{
	ClearText();
}

void Text::SetText(std::string text)
{
	if (originalText == text)
		return;

	originalText = text;

	ClearText();

	Rendering* rendering = Rendering::GetReference();
	
	for (int i = 0; i < text.size(); i++)
	{
		Sprite letterSprite = rendering->GetLetterTexture(text[i]);
		SpriteObject* newLetter = new SpriteObject(letterSprite, (int)LayerType::Overlay);
		newLetter->SetPosition(Vector2(i * 8, 0) + position);
		newLetter->SetOffsetStatic(offsetStatic);
		myLetters.push_back(newLetter);
	}
}

void Text::SetOffsetStatic(bool var)
{
	offsetStatic = var;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->SetOffsetStatic(var);
}

void Text::SetPosition(Vector2 pos)
{
	Vector2 translationPos = pos - position;

	position = pos;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->Translate(translationPos);
}

Vector2 Text::GetPosition()
{
	return position;
}

void Text::Translate(Vector2 pos)
{
	position += pos;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->Translate(pos);
}

void Text::Enable(bool var)
{
	if (enabled == var)
		return;

	enabled = var;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->Enable(enabled);
}

bool Text::IsEnabled()
{
	return enabled;
}

void Text::ClearText()
{
	for (size_t i = 0; i < myLetters.size(); i++)
		delete myLetters[i];

	myLetters.clear();
}

