#include "SimilarityCalculator.h"
#include <cstdlib>
#include <cmath>

using namespace std;

int SimilarityCalculator::calculate(const vector<Rating> &user1, const vector<Rating> &user2)
{
  int commonCount = 0;       // 공통으로 평가한 영화 개수
  double scoreDiffSum = 0.0; // 평점 차이의 절댓값 누적 합

  for (const auto &r1 : user1)
  {
    for (const auto &r2 : user2)
    {
      if (r1.getMovieId() == r2.getMovieId())
      {
        commonCount++;
        scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
      }
    }
  }

  // [엣지 케이스 4] 공통 영화가 하나도 없다면 -100 즉시 리턴
  if (commonCount == 0)
  {
    return -100;
  }

  // 유사도 공식 적용 점환산 (정수형 캐스팅)
  return static_cast<int>(commonCount * 10 - scoreDiffSum);
}