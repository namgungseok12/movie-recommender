#pragma once
#include <iostream>

using namespace std;

class Rating
{
private:
  int userId;   // 평가한 사용자 ID
  int movieId;  // 평가 대상 영화 ID
  double score; // 평점 (0.0 ~ 5.0)

public:
  // 기본 생성자
  Rating();

  // 매개변수 생성자 (점수 유효성 검사 필수)
  Rating(int uId, int mId, double s);

  // Getter (조회용, const 준수)
  int getUserId() const;
  int getMovieId() const;
  double getScore() const;

  // 정보 출력
  void display() const;
};