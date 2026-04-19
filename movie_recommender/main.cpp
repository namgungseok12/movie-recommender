#include <iostream>
#include "Movie.h"
#include "MovieManager.h"
#include "User.h"
#include "UserManager.h"
#include "Rating.h"
#include "RatingManager.h"

using namespace std;

int main()
{
  MovieManager movieManager;
  UserManager userManager;
  RatingManager ratingManager;

  // 영화 생성
  Movie m1(1, "인셉션", "SF", 2010);
  Movie m2(2, "기생충", "드라마", 2019);
  Movie m3(3, "인터스텔라", "SF", 2014);

  // 영화에 평점 추가
  m1.addRating(4.8);
  m1.addRating(4.5);

  m2.addRating(5.0);

  m3.addRating(4.2);
  m3.addRating(4.4);

  // MovieManager 테스트
  movieManager.addMovie(m1);
  movieManager.addMovie(m2);
  movieManager.addMovie(m3);

  cout << "\n--- [정렬 전 영화 목록] ---" << endl;
  movieManager.printAll();

  movieManager.sortByRating();

  cout << "\n--- [평점순 정렬 후 영화 목록] ---" << endl;
  movieManager.printAll();

  cout << "\n--- [제목 검색 테스트] ---" << endl;
  Movie *foundMovie = movieManager.findByTitle("인셉션");
  if (foundMovie != nullptr)
  {
    foundMovie->display();
  }
  else
  {
    cout << "영화를 찾을 수 없습니다." << endl;
  }

  // UserManager 테스트
  userManager.addUser(User(101, "남궁석", "nam@gmail.com"));
  userManager.addUser(User(102, "홍길동", "hong.ssu.ac.kr"));
  userManager.addUser(User(103, "이순신", "lee@gmail.com"));

  cout << "\n--- [사용자 목록] ---" << endl;
  userManager.printAll();

  cout << "\n--- [이름 검색 테스트] ---" << endl;
  User *foundUser = userManager.findByName("이순신");
  if (foundUser != nullptr)
  {
    foundUser->display();
  }
  else
  {
    cout << "사용자를 찾을 수 없습니다." << endl;
  }

  // RatingManager 테스트
  ratingManager.addRating(Rating(101, 1, 4.5));
  ratingManager.addRating(Rating(103, 1, 5.0));
  ratingManager.addRating(Rating(101, 2, 4.0));
  ratingManager.addRating(Rating(103, 3, 4.8));

  cout << "\n--- [전체 평점 목록] ---" << endl;
  ratingManager.printAll();

  cout << "\n--- [영화 ID 1의 평점 목록] ---" << endl;
  ratingManager.printRatingsByMovieId(1);

  cout << "\n영화 ID 1 평균 평점: "
       << ratingManager.getAverageRatingByMovieId(1) << endl;

  cout << "\n--- [중복 평점 검사 테스트] ---" << endl;
  if (ratingManager.hasRating(101, 1))
  {
    cout << "사용자 101은 이미 영화 1에 평점을 남겼습니다." << endl;
  }
  else
  {
    cout << "사용자 101은 영화 1에 아직 평점을 남기지 않았습니다." << endl;
  }

  return 0;
}