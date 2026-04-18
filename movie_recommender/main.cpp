#include <iostream>
#include <vector>
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"
#include "MovieManager.h"

using namespace std;

int main()
{
  MovieManager movieManager;

  vector<User> users;
  vector<Rating> ratings;

  Movie m1(1, "인셉션", "SF", 2010);
  Movie m2(2, "기생충", "드라마", 2019);

  m1.addRating(4.8);
  m1.addRating(4.5);
  m2.addRating(5.0);

  movieManager.addMovie(m1);
  movieManager.addMovie(m2);

  cout << "\n--- [정렬 전 영화 목록] ---" << endl;
  movieManager.printAll();

  movieManager.sortByRating();

  cout << "\n--- [평점순 정렬 후 영화 목록] ---" << endl;
  movieManager.printAll();

  cout << "\n--- [제목 검색 테스트] ---" << endl;
  Movie *found = movieManager.findByTitle("인셉션");
  if (found != nullptr)
  {
    found->display();
  }
  else
  {
    cout << "영화를 찾을 수 없습니다." << endl;
  }

  return 0;
}