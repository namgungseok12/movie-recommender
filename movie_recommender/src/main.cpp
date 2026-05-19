#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include "Menu.h"

int main()
{
  MovieManager movieManager;
  UserManager userManager;
  RatingManager ratingManager;
  Recommender recommender(movieManager, userManager, ratingManager);

  // 1. 파일 데이터 로드
  movieManager.loadFromFile("data/movies.csv");
  userManager.loadFromFile("data/users.csv");
  ratingManager.loadFromFile("data/ratings.csv");

  // 2. Menu 전담 제어 객체 생성 및 구동
  Menu menu(movieManager, userManager, ratingManager, recommender);
  menu.run();

  // 3. 종료 직전 자동 저장
  movieManager.saveToFile("data/movies.csv");
  userManager.saveToFile("data/users.csv");
  ratingManager.saveToFile("data/ratings.csv");

  return 0;
}