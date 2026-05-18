#pragma once
#include <vector>
#include "Rating.h"

class SimilarityCalculator
{
public:
  // 두 사용자의 평점 목록을 비교하여 유사도 점수를 정적으로 반환합니다.
  static int calculate(const std::vector<Rating> &user1, const std::vector<Rating> &user2);
};