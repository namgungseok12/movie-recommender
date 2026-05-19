#pragma once
#include <iostream>

// 사용자가 특정 영화에 남긴 평점 수치 보관 클래스
class Rating
{
private:
  int userId;   // 평점을 매긴 유저의 ID
  int movieId;  // 평점이 매겨진 영화의 ID
  double score; // 평점 점수 (0.0 ~ 5.0)

public:
  Rating();
  Rating(int uId, int mId, double s);

  int getUserId() const;
  int getMovieId() const;
  double getScore() const;

  // 평점 범위 유효성 검증 함수 (0.0 이상 5.0 이하)
  static bool isValidScore(double score);

  // 연산자 오버로딩
  friend std::ostream &operator<<(std::ostream &os, const Rating &rating);
};