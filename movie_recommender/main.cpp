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

  do
  {
    cout << "\n=== Movie Recommender ===" << endl;
    cout << "[ 영화 ]" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 제목으로 검색" << endl;
    cout << "3. 전체 목록 출력" << endl;
    cout << "4. 평점순 정렬 출력" << endl;
    cout << "[ 사용자 ]" << endl;
    cout << "5. 사용자 추가" << endl;
    cout << "6. 사용자 목록 출력" << endl;
    cout << "[ 평점 ]" << endl;
    cout << "7. 평점 입력" << endl;
    cout << "8. 영화별 평점 보기" << endl;
    cout << "0. 종료" << endl;
    cout << "선택 > ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

    case 2:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

    case 3:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

    case 4:
      cout << "아직 구현되지 않았습니다." << endl;
      break;

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