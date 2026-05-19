#include "Recommender.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "User.h"
#include <iostream>
#include <algorithm> // std::sort 사용 [cite: 317]
#include <set>       // std::set 사용 [cite: 335]
#include <map>       // std::map 사용 [cite: 362]
#include <cmath>
#include <cstdlib> // std::abs 사용 [cite: 248]

using namespace std;

Recommender::Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr)
    : movieManager(movieMgr), userManager(userMgr), ratingManager(ratingMgr) // 생성자 초기화 리스트 적용 [cite: 276]
{
}

// 유사도 계산 함수 핵심 로직 (슬라이드 4 요구사항) [cite: 235]
int Recommender::Similaritycalculate(const vector<Rating> &ratingsA, const vector<Rating> &ratingsB)
{
  int commonCount = 0;
  double scoreDiffSum = 0.0;

  // 이중 루프를 돌며 공통 영화 ID 매칭 [cite: 241, 242, 243]
  for (const auto &r1 : ratingsA) // range-for 문 사용 [cite: 247]
  {
    for (const auto &r2 : ratingsB)
    {
      if (r1.getMovieId() == r2.getMovieId())
      {
        commonCount++;
        scoreDiffSum += std::abs(r1.getScore() - r2.getScore()); // abs() 함수 적용 [cite: 244, 248]
      }
    }
  }

  // [엣지 케이스 4] 공통 영화가 0개일 때 특수값 -100 반환 (슬라이드 12 요구사항) [cite: 391, 392]
  if (commonCount == 0)
  {
    return -100;
  }

  return static_cast<int>(commonCount * 10 - scoreDiffSum);
}

// 추천 알고리즘 5단계 흐름 구현 (슬라이드 8 요구사항) [cite: 283]
std::vector<Movie> Recommender::recommend(const string &userName, int k, int n) const
{
  vector<Movie> recommendedMovies;

  // [1단계] 내 평점 가져오기 및 empty() 체크 [cite: 284, 285]
  const User *targetUser = userManager.findByName(userName);
  if (targetUser == nullptr)
  {
    return recommendedMovies; // 사용자를 찾을 수 없으면 빈 벡터 반환 [cite: 386]
  }

  int targetId = targetUser->getId();
  vector<Rating> targetRatings = ratingManager.findByUser(targetId);

  // [엣지 케이스 1] 평점 기록이 없는 유저 -> 추천 불가 처리 (슬라이드 12 요구사항) [cite: 385, 386]
  if (targetRatings.empty())
  {
    return recommendedMovies; // 빈 벡터 반환 [cite: 285, 386]
  }

  // [2단계] 모든 사용자와 유사도 계산 (자기 자신은 제외) [cite: 287, 288]
  vector<int> allUserIds = ratingManager.getAllUserIds();
  vector<pair<int, int>> similarities; // userId와 유사도 쌍을 저장할 pair 벡터 (슬라이드 9 요구사항) [cite: 306, 310, 316]

  for (int otherId : allUserIds)
  {
    if (otherId == targetId)
      continue; // 자기 자신 제외 [cite: 288]

    vector<Rating> otherRatings = ratingManager.findByUser(otherId);
    int sim = Similaritycalculate(targetRatings, otherRatings);

    // 공통 영화가 없는(-100점) 유저는 연산군에서 완전 제외
    if (sim != -100)
    {
      similarities.push_back({otherId, sim}); // pair 추가 [cite: 311]
    }
  }

  if (similarities.empty())
  {
    return recommendedMovies;
  }

  // [3단계] 유사도 상위 K명 선택 (sort + 람다 내림차순 정렬) (슬라이드 9 요구사항) [cite: 291, 292, 317, 318]
  sort(similarities.begin(), similarities.end(), [](const pair<int, int> &a, const pair<int, int> &b)
       {
         return a.second > b.second; // > 이므로 내림차순 정렬 [cite: 320, 321]
       });                           // 람다식 정렬 [cite: 319, 322]

  // [엣지 케이스 2] 유사 사용자 K명 미만일 때 있는 만큼만 사용 (슬라이드 12 요구사항) [cite: 387, 388]
  int actualK = min(k, static_cast<int>(similarities.size()));

  // [4단계] 후보 영화 수집 (K명이 높게 평가 + 내가 안 본 것) [cite: 295, 296]
  // 중복 없는 빠른 영화 탐색을 위해 std::set 구조 필수 활용 (슬라이드 10 요구사항) [cite: 328, 329]
  set<int> watchedMovieIds; // 중복 없이 값 저장 [cite: 329, 336]
  for (const auto &r : targetRatings)
  {
    watchedMovieIds.insert(r.getMovieId()); // 내가 본 영화 ID 추가 [cite: 337]
  }

  // 영화별 추천 점수 누적을 위해 std::map 필수 활용 (슬라이드 11 요구사항) [cite: 359, 361, 363]
  map<int, double> movieScores;

  for (int i = 0; i < actualK; ++i)
  {
    int neighborId = similarities[i].first; // first로 userId 접근 [cite: 308]
    vector<Rating> neighborRatings = ratingManager.findByUser(neighborId);

    for (const auto &rating : neighborRatings)
    {
      // 내가 안 본 영화인 경우에만 점수 누적 (find == end 패턴 적용) [cite: 347, 348, 350]
      if (watchedMovieIds.find(rating.getMovieId()) == watchedMovieIds.end())
      {
        movieScores[rating.getMovieId()] += rating.getScore(); // 맵에 점수 자동 누적 [cite: 368, 372]
      }
    }
  }

  if (movieScores.empty())
  {
    return recommendedMovies;
  }

  // [5단계] 점수 계산 & 정렬 반환 (vector<pair>로 변환 후 내림차순 sort) (슬라이드 11 요구사항) [cite: 299, 300, 375, 376]
  vector<pair<int, double>> sortedScores(movieScores.begin(), movieScores.end());
  sort(sortedScores.begin(), sortedScores.end(), [](const pair<int, double> &a, const pair<int, double> &b)
       {
         return a.second > b.second; // 추천 점수 내림차순 정렬 [cite: 378]
       });                           // 람다 정렬 [cite: 377]

  // [엣지 케이스 3] 추천할 영화 N개 미만일 때 있는 만큼만 반환 (슬라이드 12 요구사항) [cite: 389, 390]
  int actualN = min(n, static_cast<int>(sortedScores.size()));
  for (int i = 0; i < actualN; ++i)
  {
    const Movie *movie = movieManager.findById(sortedScores[i].first); // 가장 점수 높은 영화 추출 [cite: 379]
    if (movie != nullptr)
    {
      recommendedMovies.push_back(*movie);
    }
  }

  return recommendedMovies;
}