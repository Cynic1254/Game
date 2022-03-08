#include "game.h"

#include "RenderComponent.h"
#include "Transform.h"
#include "PlayerController.h"
#include "surface.h"
#include "BoxCollider.h"
#include "Fysics.h"

#include "settings.h"

#include <SDL_scancode.h>
#include <cassert>

#include <cmath>

namespace Tmpl8
{
	Surface tileMap("assets/IceTileset.png");
	Surface iceTile(tileSize, tileSize, tileMap.GetBuffer() + 2 * (tileMap.GetPitch() * tileSize), tileMap.GetPitch());

	Game* Game::theGame = nullptr;

	Game::Game() {
		assert(theGame == nullptr);
		theGame = this;

		background = new Surface(ScreenWidth + tileSize * 2, ScreenHeight + tileSize * 2);
		background->Clear(0);

		for(int i = 0; i < background->GetWidth(); i += tileSize)
			for (int j = 0; j < background->GetHeight(); j += tileSize)
			{
				iceTile.CopyTo(background, i, j);
			}

	}

	Game::~Game() {
		theGame = nullptr;
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
		player->AddComponent<Transform>(Tmpl8::vec2{ 500.0f, (screen->GetHeight() / 2.0f) - tileSize / 2.0f});
		player->AddComponent<PlayerController>();
		player->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { 32.0f, 32.0f }, { 10.0f, 10.0f }), CollisionType::block);
		player->AddComponent<Fysics>();
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

		float playerX = Tmpl8::Game::Get().GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float playerY = PlayerController::GetYMovement();

		if (playerX > leftScreenBound + screen->GetWidth() / 2 - tileSize / 2 &&
			playerX < rightScreenBound - screen->GetWidth() / 2 + tileSize / 2)
		{
			backgroundOffset = { (float)fmod(player->GetComponent<Transform>()->GetPosition().x, tileSize),
							(float)fmod(backgroundOffset.y + playerY, tileSize) };
		}
		else
		{
			backgroundOffset = { backgroundOffset.x, (float)fmod(backgroundOffset.y + playerY, tileSize) };
		}
		
		background->CopyTo(screen, -(backgroundOffset.x + tileSize), -(backgroundOffset.y + tileSize));

		Timer::Get().Tick();

		player->Update();
		player->Render(*screen);

		for (auto e : entities)
		{
			e->Update();
			e->Render(*screen);
		}
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
};
