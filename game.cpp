#include "game.h"

#include <cassert>
#include <cmath>
#include <SDL_scancode.h>

#include "BoxCollider.h"
#include "EntityManager.h"
#include "Physics.h"
#include "Menu.h"
#include "ObjectController.h"
#include "PlayerController.h"
#include "RenderComponent.h"
#include "settings.h"
#include "surface.h"
#include "Transform.h"
#include "Wrap.h"


namespace tmpl8
{
  void DrawBackground(const Surface* background);

  Surface tileMap("assets/IceTileset.png");
  Surface iceTile(settings::tileSize, settings::tileSize,
    tileMap.GetBuffer() + 2 * (tileMap.GetPitch() * settings::tileSize), tileMap.GetPitch());

  Surface treeTile(settings::tileSize, settings::tileSize * 2);
  Surface rock(settings::tileSize, settings::tileSize);
  Surface log(settings::tileSize, settings::tileSize);
  Surface sign(settings::tileSize, settings::tileSize);


  Surface treeBorder(settings::tileSize, ScreenHeight + settings::tileSize * 3);

  Game* Game::theGame = nullptr;

  Game::Game(const vec2 screenRes, bool isFullscreen) :
    isFullscreen(isFullscreen),
    screenSize(screenRes)
  {
    assert(theGame == nullptr);
    theGame = this;

    background = new Surface(ScreenWidth + settings::tileSize * 2, ScreenHeight + settings::tileSize * 2);
    background->Clear(0);

    for (int i = 0; i < background->GetWidth(); i += settings::tileSize)
      for (int j = 0; j < background->GetHeight(); j += settings::tileSize)
      {
        iceTile.CopyTo(background, i, j);
      }

    const Surface tempTreeTile(settings::tileSize, settings::tileSize * 2, tileMap.GetBuffer(),
      tileMap.GetPitch());
    tempTreeTile.CopyTo(&treeTile, 0, 0);

    treeBorder.Clear(0);

    for (int y = 0; y < treeBorder.GetHeight(); y += 32)
    {
      tempTreeTile.Draw(&treeBorder, 0, y);
    }

    const Surface tempRockTile(settings::tileSize, settings::tileSize, tileMap.GetBuffer() + 2 * settings::tileSize + (tileMap.GetPitch() * settings::tileSize), tileMap.GetPitch());
    const Surface tempLogTile(settings::tileSize, settings::tileSize, tileMap.GetBuffer() + 3 * settings::tileSize, tileMap.GetPitch());
    const Surface tempSignTile(settings::tileSize, settings::tileSize, tileMap.GetBuffer() + 2 * settings::tileSize, tileMap.GetPitch());

    tempRockTile.CopyTo(&rock, 0, 0);
    tempLogTile.CopyTo(&log, 0, 0);
    tempSignTile.CopyTo(&sign, 0, 0);

    entityManager = new EntityManager(entities);
    menu = new Menu();
    heart = new Surface("assets/UI/heart.png");

    player = new Entity;
    player->AddComponent<RenderComponent>(new Surface("assets/skier_32.png"), 6);
    player->AddComponent<Transform>(vec2{
      500.0f, (static_cast<float>(ScreenHeight) / 2.0f) - settings::tileSize / 2.0f
      });
    player->AddComponent<PlayerController>();
    player->AddComponent<BoxCollider>(Bounds(*player, { 7.0f, 5.0f }, { 14.0f, 26.0f }), CollisionType::block);
    player->AddComponent<Physics>();

    player->SetActive(false);

    const auto border = new Entity;
    border->AddComponent<RenderComponent>(&treeBorder, 1);
    border->AddComponent<Transform>(vec2{ 0, -settings::tileSize });
    border->AddComponent<BoxCollider>(Bounds(*border, { 0.0f, 0.0f }, {
                                               static_cast<float>(treeBorder.GetWidth()),
                                               static_cast<float>(treeBorder.GetHeight())
      }), CollisionType::block);
    border->AddComponent<Wrap>();

    entities.push_back(border);

    const auto border2 = new Entity;
    border2->AddComponent<RenderComponent>(&treeBorder, 1);
    border2->AddComponent<Transform>(vec2{ settings::rightScreenBound, -settings::tileSize });
    border2->AddComponent<BoxCollider>(Bounds(*border2, { 0.0f, 0.0f }, {
                                                static_cast<float>(treeBorder.GetWidth()),
                                                static_cast<float>(treeBorder.GetHeight())
      }), CollisionType::block);
    border2->AddComponent<Wrap>();

    entities.push_back(border2);
  }

  Game::~Game()
  {
    theGame = nullptr;

    delete background;
    delete player;
    delete entityManager;
    delete menu;
    delete heart;

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
  void Game::Init()
  {
  }

  // -----------------------------------------------------------
  // Close down application
  // -----------------------------------------------------------
  // ReSharper disable once CppMemberFunctionMayBeStatic
  void Game::Shutdown()
  {
  }

  // -----------------------------------------------------------
  // Main application tick function
  // -----------------------------------------------------------
  vec2 backgroundOffset = 0.0f;

  // ReSharper disable once CppMemberFunctionMayBeConst
  void Game::Tick()
  {
    Timer::Get().Tick();

    entityManager->Update();
    assert(player->GetComponent<Transform>() != nullptr);

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

    if (running)
    {
      int drawstart = static_cast<int>(static_cast<float>(screen->GetWidth()) / 2.0f - settings::tileSize * (settings::playerLives / 2.0f));

      for (int i = 0; i < PlayerController::GetLives(); i++, drawstart += settings::tileSize)
      {
        heart->Draw(screen, drawstart, 0);
      }
    }

    menu->Render(*screen);

    if (debug)
    {
      screen->Line(mousePos.x, 0, mousePos.x, static_cast<float>(screen->GetHeight()), 0xff0000);
      screen->Line(0, mousePos.y, static_cast<float>(screen->GetWidth()), mousePos.y, 0xff0000);
    }

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

    menu->MouseDown(button);
  }

  void Game::MouseMove(int x, int y)
  {
    if (isFullscreen)
    {
      x = static_cast<int>(static_cast<float>(x) / screenSize.x * static_cast<float>(screen->GetWidth()));
      y = static_cast<int>(static_cast<float>(y) / screenSize.y * static_cast<float>(screen->GetHeight()));
    }
    else
    {
      x = static_cast<int>(static_cast<float>(x) / windowSize.x * static_cast<float>(screen->GetWidth()));
      y = static_cast<int>(static_cast<float>(y) / windowSize.y * static_cast<float>(screen->GetHeight()));
    }

    mousePos = { static_cast<float>(x), static_cast<float>(y) };

    player->MouseMove(x, y);

    for (const auto& e : entities)
    {
      e->MouseMove(x, y);
    }

    menu->MouseMove(x, y);
  }

  void Game::KeyDown(SDL_Scancode key)
  {
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
      const CollisionType collision = BoxCollider::Collides(*player, *e);
      if (collision != CollisionType::none)
      {
        if (collision == CollisionType::block)
        {
          player->GetComponent<Physics>()->CollidesWith(*player, *e);
        }
        else if (collision == CollisionType::hurt)
        {
          player->Hurt();
        }
      }
    }
  }

  void Game::AddObstacle(vec2 pos)
  {
    const int objectType = IRand(10);

    const auto object = new Entity;
    object->AddComponent<Transform>(pos);
    object->AddComponent<ObjectController>();

    switch (objectType)
    {
    case 2:
      object->AddComponent<RenderComponent>(&rock, 1);
      object->AddComponent<BoxCollider>(Bounds(*object, { 8.0f, 9.0f }, { 19.0f, 20.0f }), CollisionType::hurt);
      break;
    case 3:
      object->AddComponent<RenderComponent>(&log, 1);
      object->AddComponent<BoxCollider>(Bounds(*object, { 3.0f, 11.0f }, { 27.0f, 13.0f }), CollisionType::hurt);
      break;
    default:
      object->AddComponent<RenderComponent>(&treeTile, 1);
      object->AddComponent<BoxCollider>(Bounds(*object, { 7.0f,10.0f }, { 18.0f,51.0f }), CollisionType::hurt);
    }

    entities.push_back(object);
  }

  void Game::EndGame()
  {
    player->SetActive(false);
    for (int i = static_cast<int>(entities.size()) - 1; i >= 0; --i)
    {
      entities[i]->SetActive(false);
    }

    running = false;
    entityManager->SetActive(false);
  }

  void Game::StartGame(int difficulty)
  {
    EndGame();

    player->SetActive(true);
    for (const auto entity : entities)
    {
      entity->SetActive(true);
    }

    this->difficulty = difficulty;
    running = true;
    entityManager->SetDifficulty(difficulty);
    entityManager->SetActive(true);

    menu->SetState(2);
  }

  void Game::JoystickMove(Uint8 axis, Sint16 value) const
  {
    player->JoystickMove(axis, value);
    for (const auto entity : entities)
    {
      entity->JoystickMove(axis, value);
    }
  }

  void Game::ButtonDown(Uint8 button) const
  {
    player->ButtonDown(button);
    for (const auto entity : entities)
    {
      entity->ButtonDown(button);
    }

    menu->ButtonDown(button);
  }

  void Game::ButtonUp(Uint8 button) const
  {
    player->ButtonUp(button);
    for (const auto entity : entities)
    {
      entity->ButtonUp(button);
    }
  }

  void DrawBackground(const Surface* background)
  {
    const Game& game = Game::Get();

    const float playerX = game.GetPlayer().GetComponent<Transform>()->GetPosition().x;
    const float playerY = PlayerController::GetYMovement();

    if (playerX > settings::leftScreenBound + static_cast<float>(game.GetScreen()->GetWidth()) / 2.0f - settings::tileSize / 2.0f &&
      playerX < settings::rightScreenBound - static_cast<float>(game.GetScreen()->GetWidth()) / 2.0f + settings::tileSize / 2.0f)
    {
      backgroundOffset = {
        static_cast<float>(fmod(game.GetPlayer().GetComponent<Transform>()->GetPosition().x, settings::tileSize)),
        static_cast<float>(fmod(backgroundOffset.y + playerY, settings::tileSize))
      };
    }
    else
    {
      backgroundOffset = {
        backgroundOffset.x, static_cast<float>(fmod(backgroundOffset.y + playerY, settings::tileSize))
      };
    }

    background->CopyTo(game.GetScreen(), static_cast<int>(-(backgroundOffset.x + settings::tileSize)),
      static_cast<int>(-(backgroundOffset.y + settings::tileSize)));
  }
};
