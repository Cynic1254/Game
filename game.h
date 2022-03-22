#pragma once

#include "template.h"
#include "Entity.h"
#include "Timer.h"

#include <vector>
#include <SDL_scancode.h>

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		Game();
		~Game();

		Game(const Game& copy) = delete;
		Game& operator=(const Game& copy) = delete;

		Game(Game&& copy) = default;
		Game& operator=(Game && copy) = default;

		static Game& Get();

		Entity& GetPlayer() { return *player; }
		const std::vector<Entity*>& GetEntities() { return entities; }
		Surface* GetScreen() { return screen; }

		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick();
		void MouseUp(int button);
		void MouseDown(int button);
		void MouseMove(int x, int y);
		void KeyUp(SDL_Scancode key);
		void KeyDown(SDL_Scancode key);

		void CheckCollisions();
	private:
		Surface* screen = nullptr;
		Surface* background = nullptr;
		Entity* player = nullptr;
		std::vector<Entity*> entities;

		static Game* theGame;
	};
}; // namespace Tmpl8