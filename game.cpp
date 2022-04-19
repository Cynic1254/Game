#include "game.h"

#include <cassert>
#include <cmath>
#include <SDL_scancode.h>

#include "BoxCollider.h"
#include "EntityManager.h"
#include "Fysics.h"
#include "ObjectController.h"
#include "PlayerController.h"
#include "RenderComponent.h"
#include "settings.h"
#include "surface.h"
#include "Transform.h"
#include "Wrap.h"
#include "Start.h"


namespace tmpl8
{
	void DrawBackground(const Surface* background);

	Surface tileMap("assets/IceTileset.png");
	Surface iceTile(settings::tileSize, settings::tileSize, tileMap.GetBuffer() + 2 * (tileMap.GetPitch() * settings::tileSize), tileMap.GetPitch());
	Surface treeTile(settings::tileSize, settings::tileSize * 2);
	Surface treeBorder(settings::tileSize, ScreenHeight + settings::tileSize * 3);

	Game* Game::theGame = nullptr;

	Game::Game()
	{
		assert(theGame == nullptr);
		theGame = this;

		background = new Surface(ScreenWidth + settings::tileSize * 2, ScreenHeight + settings::tileSize * 2);
		background->Clear(0);

		for(int i = 0; i < background->GetWidth(); i += settings::tileSize)
			for (int j = 0; j < background->GetHeight(); j += settings::tileSize)
			{
				iceTile.CopyTo(background, i, j);
			}

    const Surface* tempTreeTile = new Surface(settings::tileSize, settings::tileSize * 2, tileMap.GetBuffer(), tileMap.GetPitch());
		tempTreeTile->CopyTo(&treeTile, 0, 0);

		treeBorder.Clear(0);

		for (int y = 0; y < treeBorder.GetHeight(); y += 32)
		{
			tempTreeTile->Draw(&treeBorder, 0, y);
		}

		delete tempTreeTile;

		entityManager = new EntityManager(entities);
	}

	Game::~Game() {
		theGame = nullptr;

		delete background;
		delete player;
		delete entityManager;

		for (const auto e : entities)
		{
			delete e;
		}
		entities.clear();
	}

	Game& Game::Get()
	{
		assert(theGame != nullptr);
		return *theGame;
	}

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init() {
		player = new Entity;
		player->AddComponent<RenderComponent>(new Surface("assets/skier_32.png"), 6);
		player->AddComponent<Transform>(tmpl8::vec2{ 500.0f, (static_cast<float>(screen->GetHeight()) / 2.0f) - settings::tileSize / 2.0f });
		player->AddComponent<PlayerController>();
		player->AddComponent<BoxCollider>(Bounds(*player, { 7.0f, 5.0f }, {14.0f, 26.0f }), CollisionType::block);
		player->AddComponent<Fysics>();

		Entity* border = new Entity;
		border->AddComponent<RenderComponent>(&treeBorder, 1);
		border->AddComponent<Transform>(tmpl8::vec2{ 0, -settings::tileSize });
		border->AddComponent<BoxCollider>(Bounds(*border, { 0.0f, 0.0f }, { static_cast<float>(treeBorder.GetWidth()), static_cast<float>(treeBorder.GetHeight()) }), CollisionType::block);
		border->AddComponent<Wrap>();

		entities.push_back(border);

		Entity* border2 = new Entity;
		border2->AddComponent<RenderComponent>(&treeBorder, 1);
		border2->AddComponent<Transform>(tmpl8::vec2{ settings::rightScreenBound, -settings::tileSize });
		border2->AddComponent<BoxCollider>(Bounds(*border2, { 0.0f, 0.0f }, { static_cast<float>(treeBorder.GetWidth()), static_cast<float>(treeBorder.GetHeight()) }), CollisionType::block);
		border2->AddComponent<Wrap>();

		entities.push_back(border2);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown() {}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	vec2 backgroundOffset = 0.0f;
	void Game::Tick()
  {
		entityManager->Update();
		assert(player->GetComponent<Transform>() != nullptr);

		Timer::Get().Tick();

		player->Update();

		for (const auto e : entities)
		{
			e->Update();
		}

		CheckCollisions();

		DrawBackground(background);

		player->Render(*screen);
		for (const auto e : entities)
		{
			e->Render(*screen);
		}

		RenderComponent::RenderAll();
  }

	void Game::MouseUp(int button) const
  {
		player->MouseUp(button);

		for (const auto e : entities)
		{
			e->MouseUp(button);
		}
	}

	void Game::MouseDown(int button) const
  {
		player->MouseDown(button);

		for (const auto& e : entities)
		{
			e->MouseDown(button);
		}
	}

	void Game::MouseMove(int x, int y)
  {
		mousePos = {static_cast<float>(x), static_cast<float>(y)};

		player->MouseMove(x, y);

		for (const auto& e : entities)
		{
			e->MouseMove(x, y);
		}

	}

	void Game::KeyDown(SDL_Scancode key) {

		if (key == SDL_SCANCODE_F5)
		{
			debug = !debug;
		}

		player->KeyDown(key);

		for (const auto& e : entities)
		{
			e->KeyDown(key);
		}
	}


	void Game::KeyUp(SDL_Scancode key) const
  {
		player->KeyUp(key);

		for (const auto& e : entities)
		{
			e->KeyUp(key);
		}
	}

	void Game::CheckCollisions() const
  {
		for (const auto e : entities)
		{
			if (BoxCollider::Collides(*player, *e).first != nullptr)
			{
				if (BoxCollider::Collides(*player, *e).second->GetCollisionType() == CollisionType::block)
				{
					player->CollidesWith(*e, BoxCollider::Collides(*player, *e));
				}
				else if (BoxCollider::Collides(*player, *e).second->GetCollisionType() == CollisionType::hurt)
				{
					player->Hurt();
				}
			}
		}
	}

	void Game::AddObstacle(vec2 pos)
	{
		Entity* object = new Entity;
		object->AddComponent<RenderComponent>(&treeTile, 1);
		object->AddComponent<Transform>(pos);
		object->AddComponent<BoxCollider>(Bounds(*object, 0.0f, { settings::tileSize, settings::tileSize * 2 }), CollisionType::hurt);
		object->AddComponent<ObjectController>();

		entities.push_back(object);
	}

  void Game::EndGame()
  {
		player->SetActive(false);
    for (int i = entities.size() - 1; i >= 0; --i)
    {
      entities[i]->SetActive(false);
    }

		entityManager->SetActive(false);
  }

  void DrawBackground(const Surface* background) {
    const Game& game = Game::Get();

    const float playerX = game.GetPlayer().GetComponent<Transform>()->GetPosition().x;
    const float playerY = static_cast<float>(PlayerController::GetYMovement());

		if (playerX > settings::leftScreenBound + game.GetScreen()->GetWidth() / 2 - settings::tileSize / 2 &&
			playerX < settings::rightScreenBound - game.GetScreen()->GetWidth() / 2 + settings::tileSize / 2)
		{
			backgroundOffset = { static_cast<float>(fmod(game.GetPlayer().GetComponent<Transform>()->GetPosition().x, settings::tileSize)),
													 static_cast<float>(fmod(backgroundOffset.y + playerY, settings::tileSize)) };
		}
		else
		{
			backgroundOffset = { backgroundOffset.x, static_cast<float>(fmod(backgroundOffset.y + playerY, settings::tileSize)) };
		}

		background->CopyTo(game.GetScreen(), static_cast<int>(-(backgroundOffset.x + settings::tileSize)), static_cast<int>(-(backgroundOffset.y + settings::tileSize)));
	}
};