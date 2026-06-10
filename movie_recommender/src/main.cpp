#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include "Menu.h"

#include <iostream>
#include <exception>

using namespace std;

int main()
{
  try
  {
    MovieManager movieManager;
    UserManager userManager;
    RatingManager ratingManager;
    Recommender recommender(movieManager, userManager, ratingManager);

    // 1. 파일 데이터 로드
    movieManager.loadFromFile("data/movies_1000.csv");
    userManager.loadFromFile("data/users_1000.csv");
    ratingManager.loadFromFile("data/ratings_1000.csv");

    // 2. Menu 전담 제어 객체 생성 및 구동
    Menu menu(movieManager, userManager, ratingManager, recommender);
    menu.run();

    // 3. 종료 직전 자동 저장
    movieManager.saveToFile("data/movies_1000.csv");
    userManager.saveToFile("data/users_1000.csv");
    ratingManager.saveToFile("data/ratings_1000.csv");
  }
  catch (const exception &e)
  {
    cerr << "[프로그램 오류] " << e.what() << endl;
    return 1;
  }

  return 0;
}