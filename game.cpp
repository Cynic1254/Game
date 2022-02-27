#include "game.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "PlayerController.h"
#include "surface.h"
#include "BoxCollider.h"

#include <SDL_scancode.h>
#include <cassert>

constexpr int tileSize = 32;

namespace Tmpl8
{
	Surface tileMap("assets/IceTileset.png");
	Surface iceTile(tileSize, tileSize, tileMap.GetBuffer() + 2 * (tileMap.GetPitch() * tileSize), tileMap.GetPitch());

	Game* Game::theGame = nullptr;

	Game::Game() {
		assert(theGame == nullptr);
		theGame = this;

		backGround = new Surface(ScreenWidth + tileSize * 2, ScreenHeight + tileSize * 2);
		backGround->Clear(0);

		for(int i = 0; i < backGround->GetWidth(); i += tileSize)
			for (int j = 0; j < backGround->GetHeight(); j += tileSize)
			{
				iceTile.CopyTo(backGround, i, j);
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

		Entity* box = new Entity;

		box->AddComponent<RenderComponent>(new Surface("assets/ball.png"), 1);
		box->AddComponent<Transform>(Tmpl8::vec2{ (float)(screen->GetWidth() / 2), (float)(screen->GetHeight() / 2) }, true);
		box->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { 50.0f, 50.0f }), CollisionType::none);

		entities.push_back(box);

		Entity* player = new Entity;
		player->AddComponent<RenderComponent>(new Surface("assets/ctankbase.tga"), 16);
		player->AddComponent<Transform>();
		player->AddComponent<PlayerController>();
		player->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { 32.0f, 32.0f }, { 10.0f, 10.0f }), CollisionType::block);

		entities.push_back(player);
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown() {}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick() {
		//iceTile.CopyTo(screen, 0, 0);
		backGround->CopyTo(screen, -((int)Transform::GetScreenPosition().x % tileSize), -((int)Transform::GetScreenPosition().y % tileSize));
		Timer::Get().Tick();

		for (auto e : entities)
		{
			e->Update();
			e->Render(*screen);
		}
	}

	void Game::MouseUp(int key) {
		for (auto e : entities)
		{
			e->MouseUp(key);
		}
	}

	void Game::MouseDown(int key) {
		for (auto& e : entities)
		{
			e->MouseDown(key);
		}
	}

	void Game::MouseMove(int x, int y) {
		for (auto& e : entities)
		{
			e->MouseMove(x, y);
		}
	}

	void Game::KeyDown(SDL_Scancode key) {
		for (auto& e : entities)
		{
			e->KeyDown(key);
		}
	}

	void Game::KeyUp(SDL_Scancode key) {
		for (auto& e : entities)
		{
			e->KeyUp(key);
		}
	}
};
