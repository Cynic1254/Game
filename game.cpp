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
	Game* Game::theGame = nullptr;

	Game::Game() {
		assert(theGame == nullptr);

		theGame = this;
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
		box->AddComponent<Transform>(Tmpl8::vec2{ (float)(screen->GetWidth() / 2), (float)(screen->GetHeight() / 2) });
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
		screen->Clear(0);
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
