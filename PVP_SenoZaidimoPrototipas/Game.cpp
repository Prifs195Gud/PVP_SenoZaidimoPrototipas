#include <Game.h>
#include <Windows.h> // GetAsyncKeyState
#include <GameMap.h>
#include <Rendering.h>
#include <Vectors.h>

Game* Game::singleton = nullptr;

#define GAME_BASE_RESOLUTION Vector2(256,240)

Game::Game()
{
	gameWindow = nullptr;
	currentGameState = GameState::MainMenu;
	paused = false;
	pressedPause = false;
	gameQuit = false;
	hasInitialized = false;
	loopStarted = false;
	playerHud = nullptr;

	if (singleton == nullptr)
	{
		singleton = this;
		Initialize();
	}
}

Game::~Game()
{
}

void Game::Initialize()
{
	if (hasInitialized)
		return;
	hasInitialized = true;

	Rendering* rendering = Rendering::GetReference();
	Vector2 ResScale = rendering->GetRenderScale();

	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Sukuriam langa
	Vector2 mainRes = GAME_BASE_RESOLUTION;

	gameWindow = SDL_CreateWindow("Seno zaidimo prototipas - platformeris",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int)(mainRes.x * ResScale.x), (int)(mainRes.y * ResScale.y),
		SDL_WINDOW_SHOWN);

	// Sukuriam renderer
	SDL_Renderer* mainRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	rendering->SetRenderer(mainRenderer);

	// Pakraunam tileSet
	SDL_Surface* Surface = SDL_LoadBMP("Tileset.bmp");
	rendering->SetTileset(SDL_CreateTextureFromSurface(mainRenderer, Surface));
	SDL_FreeSurface(Surface);

	// Zaidejo UI
	playerHud = PlayerHUD::GetReference();

	StartMainLoop();
}

void Game::StartMainLoop()
{
	if (loopStarted)
		return;
	loopStarted = true;
	MainLoop();
}

void Game::StartNewGame()
{
	currentGameState = GameState::InGame;
	mainMenu.Enable(false);

	LoadLevel(1,1);
}

void Game::LoadLevel(int world, int level)
{
	GameMap::GetReference()->LoadMap(world, level);
}

void Game::SpawnPlayer()
{
}

void Game::TickMainMenu()
{
	mainMenu.Tick();
	TickTickables();
}

void Game::TickCollision()
{
}

void Game::TickTickables()
{
	vector<Tickable*>* ticks = Tickable::GetAllTicks();

	for (size_t i = 0; i < ticks->size(); i++)
		ticks->at(i)->Tick();
}

void Game::TickInGame()
{
	TickTickables();
	TickCollision();
}

void Game::MainLoop()
{
	while (!gameQuit && !GetAsyncKeyState(VK_ESCAPE))
	{
		bool run = true;
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) run = false;

		if (!run)
			break;

		SDL_Delay(17);

		if (GetAsyncKeyState('P'))
		{
			if(pressedPause != true)
				paused = !paused;

			pressedPause = true;
		}
		else
			pressedPause = false;

		if (!paused)
		{
			switch (currentGameState)
			{
			case GameState::MainMenu:
				TickMainMenu();
				break;

			case GameState::InGame:
				TickInGame();
				break;

			default:
				break;
			}

			Rendering::GetReference()->RenderWindow();
		}
	}

	if(!gameQuit)
		QuitGame();
}

void Game::QuitGame()
{
	gameQuit = true;

	SDL_Renderer* renderer = Rendering::GetReference()->GetRenderer();

	if(renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}

Game* Game::GetReference()
{
	if (singleton == nullptr)
		return new Game();

	return singleton;
}