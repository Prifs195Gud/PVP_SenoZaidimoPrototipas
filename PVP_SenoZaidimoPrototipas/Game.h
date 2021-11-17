#pragma once

#include <SDL.h>
#include <MainMenu.h>
#include <HUD.h>

enum class GameState
{
	MainMenu = 0,
	InGame
};

class Game
{
public:
	Game();
	~Game();

	void StartNewGame();

	static Game* GetReference();

	void QuitGame();

private:
	static Game* singleton;

	bool paused, pressedPause, gameQuit, hasInitialized, loopStarted;

	MainMenu mainMenu;
	PlayerHUD* playerHud;

	GameState currentGameState;
	SDL_Window* gameWindow;

	void Initialize();

	void TickTickables();
	void TickInGame();
	void TickMainMenu();
	void TickCollision();

	void StartMainLoop();
	void MainLoop();

	void LoadLevel(int lvl);
	void SpawnPlayer();
};