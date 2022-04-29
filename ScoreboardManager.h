#pragma once
#include <map>
#include <string>

class ScoreboardManager
{
public:
  ScoreboardManager();
  ~ScoreboardManager();

  static void AddScore(int score, const char* name);
  static const std::multimap<int, std::string, std::greater<>>& GetScores() {return scores;}
private:
  static void LoadScores();
  static void SaveScores();
  static std::multimap<int, std::string, std::greater<>> scores;
};
