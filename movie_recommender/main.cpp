#include <iostream>
#include "Movie.h"
#include "MovieManager.h"

using namespace std;

int main()
{
  MovieManager movieManager;

  Movie m1(1, "인셉션", "SF", 2010);
  Movie m2(2, "기생충", "드라마", 2019);
  Movie m3(3, "인터스텔라", "SF", 2014);

  m1.addRating(4.8);
  m1.addRating(4.5); // 평균 4.65

  m2.addRating(5.0); // 평균 5.0

  m3.addRating(4.2);
  m3.addRating(4.4); // 평균 4.3

  movieManager.addMovie(m1);
  movieManager.addMovie(m2);
  movieManager.addMovie(m3);

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