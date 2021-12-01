
#include <GameCamera.h>
#include <Game.h>
#include <Player.h>

GameCamera* GameCamera::singleton = nullptr;

GameCamera* GameCamera::GetReference()
{
	if (singleton == nullptr)
		return new GameCamera();

	return singleton;
}

bool GameCamera::IsPointInView(Vector2 point)
{
	return !(point.x < -camWidth * 0.5 + position.x) || !(point.x > camWidth * 0.5 + position.x)
		||
		!(point.y < -camHeight * 0.5 + position.y) || !(point.y > camHeight * 0.5 + position.y);
}

bool GameCamera::IsObjectInView(SpriteObject* trans)
{
	SDL_Rect a;
	a.x = (int)position.x;
	a.y = (int)position.y;
	a.w = camWidth;
	a.h = camHeight;

	SDL_Rect b = *trans->GetTextureData();
	b.x = (int)trans->GetPosition().x;
	b.y = (int)trans->GetPosition().y;

	return (abs(a.x - b.x) * 2 < (a.w + b.w)) &&
		(abs(a.y - b.y) * 2 < (a.h + b.h));
}

void GameCamera::Tick() // override Transform
{
	Transform::Tick();

	if (Game::GetReference()->GetGameState() == GameState::InGame)
	{
		Player* player = Player::GetPlayer();

		if (player != nullptr)
		{
			Vector2 newPos = player->GetPosition();
			newPos.y = defaultPos.y;

			if (newPos.x < position.x)
				newPos.x = position.x;

			SetPosition(newPos);
		}
		else
			SetPosition(defaultPos);
	}
	else
		SetPosition(defaultPos);
}

Vector2 GameCamera::GetCameraBounds()
{
	return Vector2(camWidth, camHeight);
}

GameCamera::GameCamera()
{
	singleton = this;

	Vector2 res = GAME_BASE_RESOLUTION;
	camWidth = (int)res.x;
	camHeight = (int)res.y;

	SetPosition(res * 0.5f);
	defaultPos = GetPosition();
}

GameCamera::~GameCamera()
{
}
