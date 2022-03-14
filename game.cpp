#include "game.h"

#include "RenderComponent.h"
#include "Transform.h"
#include "PlayerController.h"
#include "surface.h"
#include "BoxCollider.h"
#include "Wrap.h"

#include "settings.h"

#include <SDL_scancode.h>
#include <cassert>

#include <cmath>


namespace Tmpl8
{
	void DrawBackground(Surface* background);

	Surface tileMap("assets/IceTileset.png");
	Surface iceTile(tileSize, tileSize, tileMap.GetBuffer() + 2 * (tileMap.GetPitch() * tileSize), tileMap.GetPitch());
	Surface treeTile(tileSize, tileSize * 2);
	Surface treeBorder(tileSize, ScreenHeight + tileSize * 3);

	Game* Game::theGame = nullptr;

	Game::Game()
	{
		assert(theGame == nullptr);
		theGame = this;

		background = new Surface(ScreenWidth + tileSize * 2, ScreenHeight + tileSize * 2);
		background->Clear(0);

		for(int i = 0; i < background->GetWidth(); i += tileSize)
			for (int j = 0; j < background->GetHeight(); j += tileSize)
			{
				iceTile.CopyTo(background, i, j);
			}

		Surface* tempTreeTile = new Surface(tileSize, tileSize * 2, tileMap.GetBuffer(), tileMap.GetPitch());
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
		player->AddComponent<Transform>(Tmpl8::vec2{ 500.0f, (screen->GetHeight() / 2.0f) - tileSize / 2.0f });
		player->AddComponent<PlayerController>();
		player->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { 32.0f, 32.0f }, { 10.0f, 10.0f }), CollisionType::block);

		Entity* border = new Entity;
		border->AddComponent<RenderComponent>(&treeBorder, 1);
		border->AddComponent<Transform>(Tmpl8::vec2{ 0, -tileSize });
		border->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { (float)treeBorder.GetWidth(), (float)treeBorder.GetHeight() }), CollisionType::block);
		border->AddComponent<Wrap>();

		entities.push_back(border);

		Entity* border2 = new Entity;
		border2->AddComponent<RenderComponent>(&treeBorder, 1);
		border2->AddComponent<Transform>(Tmpl8::vec2{ rightScreenBound - treeBorder.GetWidth(), -tileSize });
		border2->AddComponent<BoxCollider>(Bounds({ 0.0f, 0.0f }, { (float)treeBorder.GetWidth(), (float)treeBorder.GetHeight() }), CollisionType::block);
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
	void Game::Tick() {
		assert(player->GetComponent<Transform>() != nullptr);

		DrawBackground(background);

		Timer::Get().Tick();

		player->Update();
		player->Render(*screen);

		for (auto e : entities)
		{
			e->Update();
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

	void DrawBackground(Surface* background) {
		Game& game = Game::Get();

		float playerX = game.GetPlayer()->GetComponent<Transform>()->GetPosition().x;
		float playerY = (float)PlayerController::GetYMovement();

		if (playerX > leftScreenBound + game.GetScreen()->GetWidth() / 2 - tileSize / 2 &&
			playerX < rightScreenBound - game.GetScreen()->GetWidth() / 2 + tileSize / 2)
		{
			backgroundOffset = { (float)fmod(game.GetPlayer()->GetComponent<Transform>()->GetPosition().x, tileSize),
							(float)fmod(backgroundOffset.y + playerY, tileSize) };
		}
		else
		{
			backgroundOffset = { backgroundOffset.x, (float)fmod(backgroundOffset.y + playerY, tileSize) };
		}

		background->CopyTo(game.GetScreen(), (int)-(backgroundOffset.x + tileSize), (int)-(backgroundOffset.y + tileSize));
	}
};