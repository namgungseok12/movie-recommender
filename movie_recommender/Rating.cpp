#include "Rating.h"
#include <iostream>

using namespace std;

// 기본 생성자: 초기화 리스트
Rating::Rating() : userId(0), movieId(0), score(0.0) {}

// 매개변수 생성자: 점수 유효성 검사 포함
Rating::Rating(int uId, int mId, double s)
    : userId(uId), movieId(mId)
{

  // 0.0 ~ 5.0 범위를 벗어나는지 확인
  if (s < 0.0 || s > 5.0)
  {
    cout << "⚠️ 경고: 잘못된 평점 입력 (" << s << "). 0.0으로 자동 설정됩니다." << endl;
    score = 0.0;
  }
  else
  {
    score = s;
  }
}

int Rating::getUserId() const { return userId; }
int Rating::getMovieId() const { return movieId; }
double Rating::getScore() const { return score; }

void Rating::display() const
{
  cout << "[Rating] User ID: " << userId
       << " | Movie ID: " << movieId
       << " | Score: " << score << endl;
}