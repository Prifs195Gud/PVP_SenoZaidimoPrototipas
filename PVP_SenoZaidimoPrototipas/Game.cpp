#include <Game.h>
#include <Windows.h> // GetAsyncKeyState
#include <GameMap.h>
#include <Rendering.h>
#include <Player.h>
#include <algorithm>    // std::sort

#include <Particle.h>
#include <chrono>

Game* Game::singleton = nullptr;

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
	SpawnPlayer();

	ParticleData dat1;
	dat1.gravityMod = 1;
	dat1.startSpeed = 1;
	dat1.startSize = 0.75;
	dat1.velocityOverLifetime = Vector2(0., -5.);
	//dat1.sizeOverLifetime = Vector2(10., 0.);

	EmissionBursts burst;
	burst.timeDelay = 1.;
	burst.count = 4;
	burst.cycles = 1;
	burst.interval = 1.;

	vector<EmissionBursts> bursts;
	bursts.push_back(burst);

	ParticleSystemData dat2;
	dat2.looping = true;
	dat2.duration = 0;
	dat2.emissionRateOverDistance = 0.05;
	dat2.emissionRateOverTime = 0;
	dat2.emissionRadius = 0;
	//dat2.particlesInheritVelocity = true;
	//dat2.emissionBursts = bursts;

	ParticleSystem* partSys = new ParticleSystem(Sprite(16, 82, 4, 4), dat1, dat2);
	partSys->SetPosition(Vector2(50, 50));
	partSys->ResetPositionTracker();
	partSys->SetVelocity(Vector2(1, 0));
}

void Game::SpawnPlayer()
{
	Player* player = new Player();
	player->SetPosition(Vector2(128, 120));
}

void Game::TickMainMenu()
{
	mainMenu.Tick();
	TickTickables();
}

bool CompareXPos(CollidableSpriteObject* a, CollidableSpriteObject* b)
{
	return a->GetPosition().x < b->GetPosition().x;
}

bool IntersectsX(CollidableSpriteObject* A, CollidableSpriteObject* B)
{
	SDL_Rect a = *A->GetLocalCollisionRect();
	SDL_Rect b = *B->GetLocalCollisionRect();

	return abs(a.x - b.x) * 2 < (a.w + b.w);
}

const int gridSize = 64;
void Game::TickCollision()
{
	vector<CollidableSpriteObject*>* colls = CollidableSpriteObject::GetAllCollidables();

	unordered_map<int, vector<CollidableSpriteObject*>> gridX;

	for (size_t i = 0; i < colls->size(); i++)
	{
		CollidableSpriteObject* coll = colls->at(i);
		int low = (int)coll->GetPosition().x - coll->GetTextureData()->w / 2 - 1;
		int high = (int)coll->GetPosition().x + coll->GetTextureData()->w / 2 + 1;

		low /= gridSize;
		high /= gridSize;

		if(low == high)
			gridX[low].push_back(colls->at(i));
		else
		{
			gridX[low].push_back(colls->at(i));
			gridX[high].push_back(colls->at(i));
		}
	}

	unordered_map<int, vector<CollidableSpriteObject*>>::iterator it = gridX.begin();

	while (it != gridX.end())
	{
		vector<CollidableSpriteObject*>* temp = &(*it).second;

		for (size_t i = 0; i < temp->size(); i++)
			for (size_t j = i + 1; j < temp->size(); j++)
			{
				CollidableSpriteObject* a = temp->at(i);
				CollidableSpriteObject* b = temp->at(j);

				if(!a->IsStatic())
					a->CheckCollision(b);
				else if(!b->IsStatic())
					b->CheckCollision(a);
			}

		it++;
	}
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

		if (GetAsyncKeyState('P'))
		{
			if(pressedPause != true)
				paused = !paused;

			pressedPause = true;
		}
		else
			pressedPause = false;

		auto t1 = std::chrono::steady_clock::now();
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
		auto t2 = std::chrono::steady_clock::now();
		auto d_milli = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

		int wait = 16 - d_milli;

		if (wait < 0)
			wait = 0;

		SDL_Delay(wait);
		//SDL_Delay(17);
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

GameState Game::GetGameState()
{
	return currentGameState;
}
