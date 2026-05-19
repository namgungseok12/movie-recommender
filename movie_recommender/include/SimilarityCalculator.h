#pragma once
#include <vector>
#include "Rating.h"

// 유사도 연산 클래스
class SimilarityCalculator
{
public:
  // A와 B의 평점 기록을 일대일 매칭하여 최종 취향 유사도 점수를 반환
  static int calculate(const std::vector<Rating> &user1, const std::vector<Rating> &user2);
};