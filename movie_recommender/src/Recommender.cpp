#include "Recommender.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "User.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <cstdlib>

using namespace std;

Recommender::Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr)
    : movieManager(movieMgr), userManager(userMgr), ratingManager(ratingMgr)
{
}

int Recommender::Similaritycalculate(const vector<Rating> &ratingsA, const vector<Rating> &ratingsB)
{
  int commonCount = 0;
  double scoreDiffSum = 0.0;

  for (const auto &r1 : ratingsA)
  {
    for (const auto &r2 : ratingsB)
    {
      if (r1.getMovieId() == r2.getMovieId())
      {
        commonCount++;
        scoreDiffSum += std::abs(r1.getScore() - r2.getScore());
      }
    }
  }

  if (commonCount == 0)
  {
    return -100;
  }

  return static_cast<int>(commonCount * 10 - scoreDiffSum);
}

std::vector<Movie> Recommender::recommend(const string &userName, int k, int n) const
{
  string reason;
  return recommend(userName, k, n, reason);
}

std::vector<Movie> Recommender::recommend(const string &userName, int k, int n, string &reason) const
{
  vector<Movie> recommendedMovies;
  reason = "";

  const User *targetUser = userManager.findByName(userName);
  if (targetUser == nullptr)
  {
    reason = "사용자를 찾을 수 없습니다.";
    return recommendedMovies;
  }

  int targetId = targetUser->getId();
  vector<Rating> targetRatings = ratingManager.findByUser(targetId);

  if (targetRatings.empty())
  {
    reason = "해당 사용자의 평점 데이터가 없어 추천을 진행할 수 없습니다.";
    return recommendedMovies;
  }

  vector<int> allUserIds = ratingManager.getAllUserIds();
  vector<pair<int, int>> similarities;

  for (int otherId : allUserIds)
  {
    if (otherId == targetId)
      continue; // 자기 자신 제외

    vector<Rating> otherRatings = ratingManager.findByUser(otherId);
    int sim = Similaritycalculate(targetRatings, otherRatings);

    // 공통 영화가 없는 유저는 추천 계산에서 제외
    if (sim != -100)
    {
      similarities.push_back({otherId, sim});
    }
  }

  if (similarities.empty())
  {
    reason = "공통으로 평가한 영화가 있는 다른 사용자가 없어 추천을 진행할 수 없습니다.";
    return recommendedMovies;
  }

  // 유사도 상위 K명 선택
  sort(similarities.begin(), similarities.end(), [](const pair<int, int> &a, const pair<int, int> &b)
       { return a.second > b.second; });

  // 유사 사용자가 K명보다 적으면 있는 만큼만 사용
  int actualK = min(k, static_cast<int>(similarities.size()));

  // 사용자가 이미 본 영화 ID 저장
  set<int> watchedMovieIds;
  for (const auto &r : targetRatings)
  {
    watchedMovieIds.insert(r.getMovieId());
  }

  // 추천 후보 영화 점수 누적
  map<int, double> movieScores;

  for (int i = 0; i < actualK; ++i)
  {
    int neighborId = similarities[i].first;
    vector<Rating> neighborRatings = ratingManager.findByUser(neighborId);

    for (const auto &rating : neighborRatings)
    {
      // 내가 안 본 영화만 추천 후보로 사용
      if (watchedMovieIds.find(rating.getMovieId()) == watchedMovieIds.end())
      {
        movieScores[rating.getMovieId()] += rating.getScore();
      }
    }
  }

  if (movieScores.empty())
  {
    reason = "추천 가능한 영화를 모두 봤습니다.";
    return recommendedMovies;
  }

  // 누적 점수 기준 내림차순 정렬
  vector<pair<int, double>> sortedScores(movieScores.begin(), movieScores.end());
  sort(sortedScores.begin(), sortedScores.end(), [](const pair<int, double> &a, const pair<int, double> &b)
       { return a.second > b.second; });

  int actualN = min(n, static_cast<int>(sortedScores.size()));

  for (int i = 0; i < actualN; ++i)
  {
    const Movie *movie = movieManager.findById(sortedScores[i].first);
    if (movie != nullptr)
    {
      recommendedMovies.push_back(*movie);
    }
  }

  if (recommendedMovies.empty())
  {
    reason = "추천 후보 영화가 영화 목록에 존재하지 않습니다.";
  }

  return recommendedMovies;
}