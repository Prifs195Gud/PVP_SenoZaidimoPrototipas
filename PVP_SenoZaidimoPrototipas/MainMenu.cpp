
#include <MainMenu.h>
#include <Vectors.h>
#include <Windows.h>
#include <Game.h>
#include <Rendering.h>

Page::Page() : currentSelection(0), position(Vector2())
{
	InitializePointer();
}

Page::Page(std::vector<std::string> btnText) : currentSelection(0), position(Vector2())
{
	InitializePointer();
	SetText(btnText);
}

Page::Page(std::vector<std::string> btnText, Sprite pointerTexture) : currentSelection(0), position(Vector2())
{
	InitializePointer();
	SetPointerTexture(pointerTexture);
	SetText(btnText);
}

Page::~Page()
{
}

void Page::SetPointerTexture(Sprite texture)
{
	pointer.SetSprite(texture);
}

void Page::Enable(bool var)
{
	for (size_t i = 0; i < text.size(); i++)
		text[i]->Enable(var);

	pointer.Enable(var);
}

void Page::GoUp()
{
	if (currentSelection - 1 < 0)
		return;

	SetPointerPosition(currentSelection - 1);
}

void Page::GoDown()
{
	if (currentSelection + (size_t)1 >= text.size())
		return;

	SetPointerPosition(currentSelection + 1);
}

void Page::SetPointerPosition(int which)
{
	currentSelection = which;

	Vector2 pos = pointer.GetPosition();
	pos.y = text[which]->GetPosition().y;
	pointer.SetPosition(pos);
}

int Page::GetCurrentSelection()
{
	return currentSelection;
}

void Page::InitializePointer()
{
	pointer = SpriteObject();
	pointer.SetPosition(Vector2(-16, 0));
}

void Page::SetText(std::vector<std::string> btnText)
{
	ClearText();

	for (int i = 0; i < btnText.size(); i++)
	{
		Text* newText = new Text(btnText[i]);
		newText->SetPosition(position + Vector2(0, i * 16));
		text.push_back(newText);
	}
}

void Page::ClearText()
{
	for (size_t i = 0; i < text.size(); i++)
		delete text[i];

	text.clear();
}

void Page::SetPosition(Vector2 pos)
{
	Vector2 translationPos = pos - position;

	position = pos;

	for (size_t i = 0; i < text.size(); i++)
		text[i]->Translate(translationPos);

	pointer.Translate(translationPos);
}

void Page::Translate(Vector2 pos)
{
	position += pos;

	for (size_t i = 0; i < text.size(); i++)
		text[i]->Translate(pos);

	pointer.Translate(pos);
}

Vector2 Page::GetPosition()
{
	return position;
}

// ******************************************

void MainMenu::InitializeTitle()
{
	title.SetPosition(Vector2(128, 68));
	title.SetSprite(Sprite(Vector2(119, 131), Vector2(176, 88)));
}

void MainMenu::InitializePages()
{
	Rendering* render = Rendering::GetReference();

	Sprite pointerTexture = Sprite(Vector2(36, 87), Vector2(8,8));

	vector<string> pageInfo;

	pageInfo.push_back("1 player game");
	pageInfo.push_back("eXit");

	Page* mainMenu = new Page(pageInfo, pointerTexture);

	mainMenu->SetPosition(Vector2(92, 140));

	pages.push_back(mainMenu);
}


MainMenu::MainMenu(): moveAmount(0), moveSpeed(2.5), currentPage(0), previousKeyState(0), enabled(true)
{
	InitializeTitle();
	InitializePages();
}

MainMenu::~MainMenu()
{
	for (size_t i = 0; i < pages.size(); i++)
		delete pages[i];
}

void MainMenu::Enable(bool var)
{
	if (enabled == var)
		return;

	enabled = var;

	title.Enable(var);

	for (size_t i = 0; i < pages.size(); i++)
		pages[i]->Enable(enabled);
}

void MainMenu::Tick()
{
	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	{
		if(previousKeyState != 1)
			pages[currentPage]->GoUp();
		previousKeyState = 1;
	}
	else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
	{
		if (previousKeyState != -1)
			pages[currentPage]->GoDown();

		previousKeyState = -1;
	}
	else
		previousKeyState = 0;

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (previousSpaceState != 1)
		{
			int selection = pages[currentPage]->GetCurrentSelection();

			switch (selection)
			{
			case 0:
				Game::GetReference()->StartNewGame();
				break;
			case 1:
				Game::GetReference()->QuitGame();
			default:
				break;
			}
		}

		previousSpaceState = 1;
	}
	else
		previousSpaceState = 0;
}
