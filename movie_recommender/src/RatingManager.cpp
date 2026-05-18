#include "RatingManager.h"
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

RatingManager::RatingManager()
{
}

void RatingManager::addRating(const Rating &rating)
{
  ratings.push_back(rating);
}

void RatingManager::printAll() const
{
  if (ratings.empty())
  {
    cout << "등록된 평점이 없습니다." << endl;
    return;
  }

  for (const Rating &rating : ratings)
  {
    cout << rating << endl;
  }
}

void RatingManager::printRatingsByMovieId(int movieId) const
{
  bool found = false;

  for (const Rating &rating : ratings)
  {
    if (rating.getMovieId() == movieId)
    {
      cout << rating << endl;
      found = true;
    }
  }

  if (!found)
  {
    cout << "해당 영화에 대한 평점이 없습니다." << endl;
  }
}

double RatingManager::getAverageRatingByMovieId(int movieId) const
{
  double total = 0.0;
  int count = 0;

  for (const Rating &rating : ratings)
  {
    if (rating.getMovieId() == movieId)
    {
      total += rating.getScore();
      count++;
    }
  }

  if (count == 0)
  {
    return 0.0;
  }

  return total / count;
}

int RatingManager::getRatingCountByMovieId(int movieId) const
{
  int count = 0;

  for (const Rating &rating : ratings)
  {
    if (rating.getMovieId() == movieId)
    {
      count++;
    }
  }

  return count;
}

bool RatingManager::hasRating(int userId, int movieId) const
{
  for (const Rating &rating : ratings)
  {
    if (rating.getUserId() == userId && rating.getMovieId() == movieId)
    {
      return true;
    }
  }

  return false;
}

vector<Rating> RatingManager::findByUser(int userId) const
{
  vector<Rating> userRatings;
  for (const auto &rating : ratings)
  {
    if (rating.getUserId() == userId)
    {
      userRatings.push_back(rating);
    }
  }
  return userRatings;
}

vector<int> RatingManager::getAllUserIds() const
{
  set<int> uniqueIds;
  for (const auto &rating : ratings)
  {
    uniqueIds.insert(rating.getUserId());
  }
  return vector<int>(uniqueIds.begin(), uniqueIds.end());
}

int RatingManager::size() const
{
  return static_cast<int>(ratings.size());
}

void RatingManager::clear()
{
  ratings.clear();
}

void RatingManager::parseLine(const string &line)
{
  stringstream ss(line);
  string token;

  getline(ss, token, ',');
  int userId = stoi(token);
  getline(ss, token, ',');
  int movieId = stoi(token);
  getline(ss, token, ',');
  double score = stod(token);

  ratings.push_back(Rating(userId, movieId, score));
}

string RatingManager::getHeader() const
{
  return "userId,movieId,score";
}

string RatingManager::formatLine(int index) const
{
  stringstream ss;
  ss << ratings[index].getUserId() << "," << ratings[index].getMovieId() << "," << ratings[index].getScore();
  return ss.str();
}