#include <iostream>
#include <vector> // vector 사용을 위해 필수 [cite: 26-27]
#include <string>
#include "Movie.h"
#include "User.h"
#include "Rating.h"

using namespace std;

int main()
{
  // 1. 각 클래스를 관리할 vector 선언
  vector<Movie> movies;
  vector<User> users;
  vector<Rating> ratings;

  // 2. 데이터 추가 (emplace_back 사용)
  movies.emplace_back(1, "인셉션", "SF", 2010);
  movies.emplace_back(2, "기생충", "드라마", 2019);

  users.emplace_back(101, "남궁석", "nam@gmail.com");
  users.emplace_back(102, "홍길동", "hong.ssu.ac.kr"); // 유효하지 않은 이메일 (경고 발생후 unknown@example.com으로 설정)
  users.emplace_back(103, "이순신", "lee@gmail.com");

  // 2.5 user 이메일 수정
  users[1].setEmail("namgungseok.ssu.ac.kr"); // ❌ 오류
  users[2].setEmail("leesunshin@gmail.com");  // 정상 변경

  // 3. 평점 데이터 추가 및 유효성 검사
  ratings.emplace_back(101, 1, 4.8);
  ratings.emplace_back(101, 2, 5.0);
  ratings.emplace_back(102, 1, 6.5); // 잘못된 평점 테스트 (경고 발생 후 0.0 설정)

  // 4. 영화 객체에 실제 평점 반영
  // ratings 벡터를 순회하며 해당 영화 ID에 맞는 평점을 추가
  for (const auto &r : ratings)
  {
    for (auto &m : movies)
    {
      if (m.getId() == r.getMovieId())
      {
        m.addRating(r.getScore());
      }
    }
  }

  // 5. 전체 데이터 출력
  cout << "\n--- [사용자 현황] (총 " << users.size() << "명) ---" << endl; // size() 활용
  for (const auto &u : users)
  {
    u.display();
  }

  cout << "\n--- [영화 및 평균 평점] ---" << endl;
  for (const auto &m : movies)
  {
    m.display();
  }

  cout << "\n--- [개별 평점 기록] ---" << endl;
  for (const auto &r : ratings)
  {
    r.display();
  }

  return 0;
}