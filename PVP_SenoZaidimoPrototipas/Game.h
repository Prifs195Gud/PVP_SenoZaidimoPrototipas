#pragma once

#include <SDL.h>
#include <MainMenu.h>
#include <HUD.h>
#include <Vectors.h>

#define GAME_BASE_RESOLUTION Vector2(256,240)
#define BASE_FRAMERATE 60

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
	GameState GetGameState();

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

	void LoadLevel(int world, int level);
	void SpawnPlayer();
};