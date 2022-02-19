#pragma once

#include <vector>
#include <Sprite.h>
#include <SpriteObject.h>
#include <Text.h>

class Page
{
public:
	Page();
	Page(std::vector<std::string> btnTex);
	Page(std::vector<std::string> btnText, Sprite pointerTexture);
	~Page();

	void Enable(bool var);

	void GoUp();
	void GoDown();

	int GetCurrentSelection();

	void SetText(vector<string> btnText);

	void ClearText();

	void SetPosition(Vector2 pos);
	void Translate(Vector2 pos);
	Vector2 GetPosition();
private:
	Vector2 position;

	void InitializePointer();
	void SetPointerTexture(Sprite texture);
	void SetPointerPosition(int which);

	int currentSelection;

	SpriteObject pointer;
	std::vector<Text*> text;
};

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Tick();
	void Enable(bool var);
private:
	bool enabled;

	int currentPage;
	int previousKeyState;
	int previousSpaceState;

	float moveAmount;
	float moveSpeed;

	SpriteObject title;

	std::vector<Page*> pages;

	void InitializeTitle();
	void InitializePages();
};