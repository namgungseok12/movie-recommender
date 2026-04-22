#include <iostream>
#include <string>
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

  int choice = -1;
  int nextUserId = 1;
  int nextMovieId = 1;

  do
  {
    cout << "\n=== Movie Recommender ===" << endl;
    cout << endl << "[ 영화 ]" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 제목으로 검색" << endl;
    cout << "3. 전체 목록 출력" << endl;
    cout << "4. 평점순 정렬 출력" << endl;
    cout << endl << "[ 사용자 ]" << endl;
    cout << "5. 사용자 추가" << endl;
    cout << "6. 사용자 목록 출력" << endl;
    cout << endl << "[ 평점 ]" << endl;
    cout << "7. 평점 입력" << endl;
    cout << "8. 영화별 평점 보기" << endl;
    cout << "0. 종료" << endl;
    cout << endl << "선택 > ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      string userName;
      string title;
      string genre;
      int year;
      double initialScore;

      cin.ignore();

      cout << "영화를 등록할 사용자 이름 입력: ";
      getline(cin, userName);

      User *foundUser = userManager.findByName(userName);
      if (foundUser == nullptr)
      {
        cout << "등록된 사용자만 영화를 추가할 수 있습니다." << endl;
        break;
      }

      cout << "영화 제목 입력: ";
      getline(cin, title);

      cout << "장르 입력: ";
      getline(cin, genre);

      cout << "개봉 연도 입력: ";
      cin >> year;

      cout << "평점 입력 (0.0 ~ 5.0): ";
      cin >> initialScore;

      Movie movie(nextMovieId, title, genre, year);
      movie.addRating(initialScore);
      movieManager.addMovie(movie);

      Rating rating(foundUser->getId(), nextMovieId, initialScore);
      ratingManager.addRating(rating);

      cout << "영화가 추가되었습니다. [ID: " << nextMovieId << "]" << endl;
      nextMovieId++;
      break;
    }

    case 2:
    {
      string title;

      cin.ignore();
      cout << "검색할 영화 제목 입력: ";
      getline(cin, title);

      Movie *foundMovie = movieManager.findByTitle(title);
      if (foundMovie != nullptr)
      {
        cout << "\n--- [검색 결과] ---" << endl;
        foundMovie->display();
      }
      else
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
      }
      break;
    }

    case 3:
    {
      cout << "\n--- [전체 영화 목록] ---" << endl;
      movieManager.printAll();
      break;
    }

    case 4:
    {
      cout << "\n--- [평점순 정렬 영화 목록] ---" << endl;
      movieManager.printSortedByRating();
      break;
    }

    case 5:
    {
      string name;
      string email;

      cin.ignore();

      cout << "사용자 이름 입력: ";
      getline(cin, name);

      cout << "이메일 입력: ";
      getline(cin, email);

      User user(nextUserId, name, email);
      userManager.addUser(user);

      cout << "사용자가 추가되었습니다. [ID: " << nextUserId << "]" << endl;
      nextUserId++;
      break;
    }

    case 6:
    {
      cout << "\n--- [사용자 목록] ---" << endl;
      userManager.printAll();
      break;
    }

    case 7:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

    case 8:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

    case 0:
      cout << "프로그램을 종료합니다." << endl;
      break;

    default:
      cout << "올바른 번호를 입력하세요." << endl;
      break;
    }

  } while (choice != 0);

  return 0;
}