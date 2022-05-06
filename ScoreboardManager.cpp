#include "ScoreboardManager.h"

#include <fstream>
#include <iostream>

static bool loadedScores = false;
static int activeManagers = 0;
std::multimap<int, std::string, std::greater<>> ScoreboardManager::scores;

struct ScoreData
{
  int score = 0;
  std::string name;
};

ScoreboardManager::ScoreboardManager()
{
  activeManagers++;
  if (!loadedScores)
    LoadScores();
}

ScoreboardManager::~ScoreboardManager()
{
  activeManagers--;
  if (!activeManagers)
    SaveScores();
}

void ScoreboardManager::AddScore(int score, const char* name)
{
  scores.insert(std::pair<int, std::string>(score, name));
}

void ScoreboardManager::LoadScores()
{
  std::ifstream file;
  file.open("scores.bin", std::ios::binary);

  if (!file)
    return;

  while (!file.eof())
  {
    ScoreData temp;
    file >> temp.score >> temp.name;
    if (!temp.name.empty() && temp.score != 0)
      scores.insert(std::pair<int, std::string>(temp.score, temp.name));
  }

  file.close();

  loadedScores = true;
}

void ScoreboardManager::SaveScores()
{
  std::ofstream file("scores.bin", std::ios::binary);

  for (const auto& score : scores)
  {
    ScoreData temp;
    temp.score = score.first;
    temp.name = score.second;

    file << score.first << " " << score.second << std::endl;
  }

  file.close();
}
