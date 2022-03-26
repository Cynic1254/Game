#pragma once

#include <SDL_scancode.h>
#include <vector>

#include "Entity.h"
#include "template.h"

class EntityManager;

namespace tmpl8 {

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

		Entity& GetPlayer() const { return *player; }
		const std::vector<Entity*>& GetEntities() { return entities; }
		Surface* GetScreen() const { return screen; }

		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick() const;
		void MouseUp(int button) const;
		void MouseDown(int button) const;
		void MouseMove(int x, int y) const;
		void KeyUp(SDL_Scancode key) const;
		void KeyDown(SDL_Scancode key);

		void CheckCollisions() const;

		void AddObstacle(vec2 pos);

		bool IsDebug() const { return debug; }
	private:
		const EntityManager* entityManager{};

		Surface* screen = nullptr;
		Surface* background = nullptr;
		Entity* player = nullptr;
		std::vector<Entity*> entities;

		static Game* theGame;

		bool debug = false;
	};
}; // namespace Tmpl8