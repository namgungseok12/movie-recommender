#pragma once
#include <string>

class MovieManager;
class UserManager;
class RatingManager;
class Recommender;

// 메뉴 UI 제어 로직 캡슐화
class Menu
{
private:
  MovieManager &movieManager;
  UserManager &userManager;
  RatingManager &ratingManager;
  Recommender &recommender;

  // 콘솔 입력 및 서브 예외 처리
  std::string readLine(const std::string &prompt) const;
  int readValidMenuChoice() const;
  bool readValidYear(int &year) const;
  bool readValidScore(double &score, const std::string &invalidMessage) const;

public:
  Menu(MovieManager &movieMgr, UserManager &userMgr, RatingManager &ratingMgr, Recommender &recom);
  void run();
};