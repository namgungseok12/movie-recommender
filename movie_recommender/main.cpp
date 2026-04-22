#include <iostream>
#include <string>
#include <limits>
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "User.h"

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

    cout << endl
         << "[ 영화 ]" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 제목으로 검색" << endl;
    cout << "3. 전체 목록 출력" << endl;
    cout << "4. 평점순 정렬 출력" << endl;

    cout << endl
         << "[ 사용자 ]" << endl;
    cout << "5. 사용자 추가" << endl;
    cout << "6. 사용자 목록 출력" << endl;

    cout << endl
         << "[ 평점 ]" << endl;
    cout << "7. 평점 입력" << endl;
    cout << "8. 영화별 평점 보기" << endl;
    cout << "0. 종료" << endl;

    cout << endl
         << "선택 > ";
    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      choice = -1;
      cout << "올바른 번호를 입력하세요." << endl;
      continue;
    }

    switch (choice)
    {
    case 1:
    {
      string userName;
      string title;
      string genre;
      int year;
      double initialScore;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "개봉 연도는 숫자로 입력하세요." << endl;
        break;
      }

      cout << "평점 입력 (0.0 ~ 5.0): ";
      cin >> initialScore;

      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "평점은 숫자로 입력하세요." << endl;
        break;
      }

      if (initialScore < 0.0 || initialScore > 5.0)
      {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "유효하지 않은 평점입니다. 영화가 추가되지 않았습니다." << endl;
        break;
      }

      Movie movie(nextMovieId, title, genre, year);
      movie.addRating(initialScore);

      if (!movieManager.addMovie(movie))
      {
        break;
      }

      Rating rating(foundUser->getId(), nextMovieId, initialScore);
      ratingManager.addRating(rating);

      cout << "영화가 추가되었습니다. [ID: " << nextMovieId << "]" << endl;
      nextMovieId++;
      break;
    }

    case 2:
    {
      string title;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "검색할 영화 제목 입력: ";
      getline(cin, title);

      Movie *foundMovie = movieManager.findByTitle(title);
      if (foundMovie != nullptr)
      {
        cout << "\n--- [검색 결과] ---" << endl;
        cout << *foundMovie << endl;
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

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "사용자 이름 입력: ";
      getline(cin, name);

      cout << "이메일 입력: ";
      getline(cin, email);

      if (!User::isValidEmail(email))
      {
        cout << "유효하지 않은 이메일 형식입니다. 사용자가 추가되지 않았습니다." << endl;
        break;
      }

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
    {
      string userName;
      string movieTitle;
      double score;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "평점을 입력할 사용자 이름 입력: ";
      getline(cin, userName);

      User *foundUser = userManager.findByName(userName);
      if (foundUser == nullptr)
      {
        cout << "등록된 사용자만 평점을 입력할 수 있습니다." << endl;
        break;
      }

      cout << "평점을 남길 영화 제목 입력: ";
      getline(cin, movieTitle);

      Movie *foundMovie = movieManager.findByTitle(movieTitle);
      if (foundMovie == nullptr)
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
        break;
      }

      if (ratingManager.hasRating(foundUser->getId(), foundMovie->getId()))
      {
        cout << "이 사용자는 이미 해당 영화에 평점을 남겼습니다." << endl;
        break;
      }

      cout << "평점 입력 (0.0 ~ 5.0): ";
      cin >> score;

      if (cin.fail())
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "평점은 숫자로 입력하세요." << endl;
        break;
      }

      if (score < 0.0 || score > 5.0)
      {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "유효하지 않은 평점입니다. 평점이 입력되지 않았습니다." << endl;
        break;
      }

      Rating rating(foundUser->getId(), foundMovie->getId(), score);
      ratingManager.addRating(rating);
      foundMovie->addRating(score);

      cout << "평점이 입력되었습니다." << endl;
      break;
    }

    case 8:
    {
      string movieTitle;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

      cout << "평점을 조회할 영화 제목 입력: ";
      getline(cin, movieTitle);

      Movie *foundMovie = movieManager.findByTitle(movieTitle);
      if (foundMovie == nullptr)
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
        break;
      }

      cout << "\n--- [" << movieTitle << " 평점 목록] ---" << endl;
      ratingManager.printRatingsByMovieId(foundMovie->getId());

      cout << "평균 평점: "
           << ratingManager.getAverageRatingByMovieId(foundMovie->getId()) << endl;
      break;
    }

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