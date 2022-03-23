#include "game.h"

#include "RenderComponent.h"
#include "Transform.h"
#include "PlayerController.h"
#include "surface.h"
#include "BoxCollider.h"
#include "Wrap.h"
#include "Fysics.h"
#include "ObjectController.h"

#include "settings.h"

#include <SDL_scancode.h>
#include <cassert>

#include <cmath>


namespace Tmpl8
{
	void DrawBackground(Surface* background);

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

		Surface* tempTreeTile = new Surface(settings::tileSize, settings::tileSize * 2, tileMap.GetBuffer(), tileMap.GetPitch());
		tempTreeTile->CopyTo(&treeTile, 0, 0);

		treeBorder.Clear(0);

		for (int y = 0; y < treeBorder.GetHeight(); y += 32)
		{
			tempTreeTile->Draw(&treeBorder, 0, y);
		}

		delete tempTreeTile;
	}

	Game::~Game() {
		theGame = nullptr;

		delete background;
		delete player;
		for (auto e : entities)
		{
			delete e;
		}
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
		player->AddComponent<RenderComponent>(new Surface("assets/ctankbase.tga"), 16);
		player->AddComponent<Transform>(Tmpl8::vec2{ 500.0f, (screen->GetHeight() / 2.0f) - settings::tileSize / 2.0f });
		player->AddComponent<PlayerController>();
		player->AddComponent<BoxCollider>(Bounds(*player, { 10.0f, 10.0f }, {32.0f, 32.0f }), CollisionType::block);
		player->AddComponent<Fysics>();

		Entity* border = new Entity;
		border->AddComponent<RenderComponent>(&treeBorder, 1);
		border->AddComponent<Transform>(Tmpl8::vec2{ 0, -settings::tileSize });
		border->AddComponent<BoxCollider>(Bounds(*border, { 0.0f, 0.0f }, { (float)treeBorder.GetWidth(), (float)treeBorder.GetHeight() }), CollisionType::block);
		border->AddComponent<Wrap>();

		entities.push_back(border);

		Entity* border2 = new Entity;
		border2->AddComponent<RenderComponent>(&treeBorder, 1);
		border2->AddComponent<Transform>(Tmpl8::vec2{ settings::rightScreenBound, -settings::tileSize });
		border2->AddComponent<BoxCollider>(Bounds(*border2, { 0.0f, 0.0f }, { (float)treeBorder.GetWidth(), (float)treeBorder.GetHeight() }), CollisionType::block);
		border2->AddComponent<Wrap>();

		entities.push_back(border2);

		Entity* object = new Entity;
		object->AddComponent<RenderComponent>(&treeTile, 1);
		object->AddComponent<Transform>(Tmpl8::vec2{ 500.0f, ScreenHeight });
		object->AddComponent<BoxCollider>(Bounds(*object, 0.0f, { settings::tileSize, settings::tileSize * 2}), CollisionType::hurt);
		object->AddComponent<ObjectController>();

		entities.push_back(object);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown() {}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	vec2 backgroundOffset = 0.0f;
	void Game::Tick() {
		assert(player->GetComponent<Transform>() != nullptr);

		DrawBackground(background);

		Timer::Get().Tick();

		player->Update();

		for (auto e : entities)
		{
			e->Update();
			e->Render(*screen);
		}

		CheckCollisions();

		player->Render(*screen);
		for (auto e : entities)
		{
			e->Render(*screen);
		}

		RenderComponent::RenderAll();
	}

	void Game::MouseUp(int key) {
		player->MouseUp(key);

		for (auto e : entities)
		{
			e->MouseUp(key);
		}
	}

	void Game::MouseDown(int key) {
		player->MouseDown(key);

		for (auto& e : entities)
		{
			e->MouseDown(key);
		}
	}

	void Game::MouseMove(int x, int y) {
		player->MouseMove(x, y);

		for (auto& e : entities)
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

		for (auto& e : entities)
		{
			e->KeyDown(key);
		}
	}


	void Game::KeyUp(SDL_Scancode key) {
		player->KeyUp(key);

		for (auto& e : entities)
		{
			e->KeyUp(key);
		}
	}

	void Game::CheckCollisions()
	{
		for (auto e : entities)
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

	void DrawBackground(Surface* background) {
		Game& game = Game::Get();

		float playerX = game.GetPlayer().GetComponent<Transform>()->GetPosition().x;
		float playerY = (float)PlayerController::GetYMovement();

		if (playerX > settings::leftScreenBound + game.GetScreen()->GetWidth() / 2 - settings::tileSize / 2 &&
			playerX < settings::rightScreenBound - game.GetScreen()->GetWidth() / 2 + settings::tileSize / 2)
		{
			backgroundOffset = { (float)fmod(game.GetPlayer().GetComponent<Transform>()->GetPosition().x, settings::tileSize),
							(float)fmod(backgroundOffset.y + playerY, settings::tileSize) };
		}
		else
		{
			backgroundOffset = { backgroundOffset.x, (float)fmod(backgroundOffset.y + playerY, settings::tileSize) };
		}

		background->CopyTo(game.GetScreen(), (int)-(backgroundOffset.x + settings::tileSize), (int)-(backgroundOffset.y + settings::tileSize));
	}
};