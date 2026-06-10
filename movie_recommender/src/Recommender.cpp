#include "Recommender.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "User.h"
#include "Timer.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <cstdlib>

using namespace std;

Recommender::Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr)
    : movieManager(movieMgr), userManager(userMgr), ratingManager(ratingMgr)
{
}

int Recommender::Similaritycalculate(const vector<Rating> &ratingsA, const vector<Rating> &ratingsB)
{
  if (ratingsA.empty() || ratingsB.empty())
  {
    return -100;
  }

  int commonCount = 0;
  double scoreDiffSum = 0.0;

  const vector<Rating> &smallerRatings =
      (ratingsA.size() <= ratingsB.size()) ? ratingsA : ratingsB;
  const vector<Rating> &largerRatings =
      (ratingsA.size() <= ratingsB.size()) ? ratingsB : ratingsA;

  unordered_map<int, double> scoreByMovieId;
  scoreByMovieId.reserve(smallerRatings.size());

  for (const Rating &rating : smallerRatings)
  {
    scoreByMovieId[rating.getMovieId()] = rating.getScore();
  }

  for (const Rating &rating : largerRatings)
  {
    auto it = scoreByMovieId.find(rating.getMovieId());

    if (it != scoreByMovieId.end())
    {
      commonCount++;
      scoreDiffSum += std::abs(it->second - rating.getScore());
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
  Perf::Timer timer("Recommender::recommend");

  vector<Movie> recommendedMovies;
  if (n > 0)
  {
    recommendedMovies.reserve(n);
  }

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
  similarities.reserve(allUserIds.size());

  for (int otherId : allUserIds)
  {
    if (otherId == targetId)
    {
      continue; // 자기 자신 제외
    }

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

  // 유사 사용자가 K명보다 적으면 있는 만큼만 사용
  int actualK = min(k, static_cast<int>(similarities.size()));
  if (actualK <= 0)
  {
    reason = "추천에 사용할 유사 사용자 수가 0명입니다.";
    return recommendedMovies;
  }

  // 유사도 상위 K명만 선택한다. 전체 정렬보다 Top-K 부분 정렬이 더 효율적이다.
  auto similarityCompare = [](const pair<int, int> &a, const pair<int, int> &b)
  {
    if (a.second != b.second)
    {
      return a.second > b.second;
    }
    return a.first < b.first;
  };

  partial_sort(similarities.begin(),
               similarities.begin() + actualK,
               similarities.end(),
               similarityCompare);

  // 사용자가 이미 본 영화 ID 저장
  unordered_set<int> watchedMovieIds;
  watchedMovieIds.reserve(targetRatings.size());

  for (const Rating &rating : targetRatings)
  {
    watchedMovieIds.insert(rating.getMovieId());
  }

  // 추천 후보 영화 점수 누적
  unordered_map<int, double> movieScores;
  movieScores.reserve(movieManager.size());

  for (int i = 0; i < actualK; ++i)
  {
    int neighborId = similarities[i].first;
    vector<Rating> neighborRatings = ratingManager.findByUser(neighborId);

    for (const Rating &rating : neighborRatings)
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

  // 누적 점수 기준으로 추천할 상위 N개만 선택한다.
  vector<pair<int, double>> sortedScores;
  sortedScores.reserve(movieScores.size());

  for (const auto &entry : movieScores)
  {
    sortedScores.push_back(entry);
  }

  int actualN = min(n, static_cast<int>(sortedScores.size()));
  if (actualN <= 0)
  {
    reason = "추천 개수가 0개입니다.";
    return recommendedMovies;
  }

  auto scoreCompare = [](const pair<int, double> &a, const pair<int, double> &b)
  {
    if (a.second != b.second)
    {
      return a.second > b.second;
    }
    return a.first < b.first;
  };

  partial_sort(sortedScores.begin(),
               sortedScores.begin() + actualN,
               sortedScores.end(),
               scoreCompare);

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