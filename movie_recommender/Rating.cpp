#include "Rating.h"
#include <iostream>

using namespace std;

Rating::Rating() : userId(0), movieId(0), score(0.0) {}

Rating::Rating(int uId, int mId, double s)
    : userId(uId), movieId(mId)
{
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

int Rating::getUserId() const
{
  return userId;
}

int Rating::getMovieId() const
{
  return movieId;
}

double Rating::getScore() const
{
  return score;
}

ostream &operator<<(ostream &os, const Rating &rating)
{
  os << "[Rating] User ID: " << rating.userId
     << " | Score: " << rating.score;
  return os;
}