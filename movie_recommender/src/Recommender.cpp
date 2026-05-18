#include "Recommender.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "SimilarityCalculator.h"
#include "User.h"
#include "Movie.h"
#include "Rating.h"
#include <iostream>
#include <vector>

using namespace std;

Recommender::Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr)
    : movieManager(movieMgr), userManager(userMgr), ratingManager(ratingMgr)
{
}

void Recommender::printRecommendations(const string &userName) const
{
  // 1. 대상 사용자 조회
  const User *targetUser = userManager.findByName(userName);
  if (targetUser == nullptr)
  {
    cout << "해당 사용자를 찾을 수 없습니다." << endl;
    return;
  }

  int targetId = targetUser->getId();
  vector<Rating> targetRatings = ratingManager.findByUser(targetId);

  // 2. 피어(가장 취향이 비슷한 유저) 찾기
  vector<int> allUserIds = ratingManager.getAllUserIds();
  int bestMatchUserId = -1;
  int maxSimilarity = -100; // 공통 영화가 없을 때의 기본 센티널 값보다 크게 초기화

  for (int otherId : allUserIds)
  {
    if (otherId == targetId)
      continue; // 나 자신은 제외

    vector<Rating> otherRatings = ratingManager.findByUser(otherId);
    int currentSimilarity = SimilarityCalculator::calculate(targetRatings, otherRatings);

    // 더 높은 유사도를 가진 사용자를 발견하면 갱신
    if (currentSimilarity > maxSimilarity)
    {
      maxSimilarity = currentSimilarity;
      bestMatchUserId = otherId;
    }
  }

  // [엣지 케이스] 다른 유저가 없거나, 모든 유저와의 유사도가 -100점(공통 영화 0개)인 경우
  if (bestMatchUserId == -1 || maxSimilarity == -100)
  {
    cout << "추천할 수 있는 비슷한 취향의 사용자가 존재하지 않습니다." << endl;
    return;
  }

  const User *similarUser = userManager.findById(bestMatchUserId);
  if (similarUser == nullptr)
    return;

  // 점수 검증용 출력 라인 (19, 14 점수 확인용)
  cout << "\n▶ 가장 비슷한 취향의 사용자: " << similarUser->getName()
       << " (취향 유사도 점수: " << maxSimilarity << "점)" << endl;

  // 3. 영화 추천 스크리닝 (상대의 평점 4.0 이상 리스트 중 내가 안 본 것)
  vector<Rating> similarUserRatings = ratingManager.findByUser(bestMatchUserId);
  bool hasRecommendation = false;

  cout << "--- [추천 영화 목록] ---" << endl;
  for (const auto &rating : similarUserRatings)
  {
    if (rating.getScore() >= 4.0)
    {
      // 내가 이미 평점을 남긴 영화인지 체크 (안 남겼어야 추천 대상)
      if (!ratingManager.hasRating(targetId, rating.getMovieId()))
      {
        const Movie *recommendedMovie = movieManager.findById(rating.getMovieId());
        if (recommendedMovie != nullptr)
        {
          cout << *recommendedMovie << " | 상대방 평점: " << rating.getScore() << endl;
          hasRecommendation = true;
        }
      }
    }
  }

  if (!hasRecommendation)
  {
    cout << "추천할 만한 고평점 영화가 없습니다." << endl;
  }
}