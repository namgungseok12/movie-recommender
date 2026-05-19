#pragma once
#include <string>
#include <vector>
#include "Movie.h"
#include "Rating.h"

// 전방 선언을 통해 헤더 파일이 서로 엉키는 문제를 차단합니다.
class MovieManager;
class UserManager;
class RatingManager;

class Recommender
{
private:
  // 원본 데이터를 안전하게 참조하기 위한 const 참조자 멤버 변수 (슬라이드 7 요구사항) [cite: 271, 272, 273]
  const MovieManager &movieManager;
  const UserManager &userManager;
  const RatingManager &ratingManager;

public:
  // 생성자 초기화 리스트를 필수 사용하도록 설계 (슬라이드 7 요구사항) [cite: 274, 275, 276]
  Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr);

  // [교수님 필수 요구사항 ①] Similaritycalculate - 대소문자 시그니처 일치 (슬라이드 4, 18 요구사항) [cite: 237, 488]
  static int Similaritycalculate(const std::vector<Rating> &ratingsA, const std::vector<Rating> &ratingsB);

  // [교수님 필수 요구사항 ②] recommend - 5단계 흐름 및 엣지 케이스 처리 (슬라이드 8, 18 요구사항) [cite: 283, 489]
  std::vector<Movie> recommend(const std::string &userName, int k, int n) const;
};