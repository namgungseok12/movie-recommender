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

  movieManager.addMovie(Movie(1, "인셉션", "SF", 2010));
  movieManager.addMovie(Movie(2, "기생충", "드라마", 2019));

  users.emplace_back(101, "남궁석", "nam@gmail.com");
  users.emplace_back(102, "홍길동", "hong.ssu.ac.kr");
  users.emplace_back(103, "이순신", "lee@gmail.com");

  users[1].setEmail("namgungseok.ssu.ac.kr");
  users[2].setEmail("leesunshin@gmail.com");

  ratings.emplace_back(101, 1, 4.8);
  ratings.emplace_back(101, 2, 5.0);
  ratings.emplace_back(102, 1, 6.5);

  cout << "\n--- [영화 목록] ---" << endl;
  movieManager.printAll();

  return 0;
}