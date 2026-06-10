#include "RatingManager.h"

#include <iostream>
#include <sstream>
#include <set>
#include <stdexcept>

using namespace std;

namespace
{
  string trim(const string &str)
  {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
      return "";
    }

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
  }

  int parseIntStrict(const string &value, const string &fieldName)
  {
    string trimmed = trim(value);

    if (trimmed.empty())
    {
      throw invalid_argument(fieldName + " 값이 비어 있습니다.");
    }

    size_t pos = 0;
    int result = 0;

    try
    {
      result = stoi(trimmed, &pos);
    }
    catch (const exception &)
    {
      throw invalid_argument(fieldName + " 값은 정수여야 합니다.");
    }

    if (pos != trimmed.size())
    {
      throw invalid_argument(fieldName + " 값에 숫자가 아닌 문자가 포함되어 있습니다.");
    }

    return result;
  }

  double parseDoubleStrict(const string &value, const string &fieldName)
  {
    string trimmed = trim(value);

    if (trimmed.empty())
    {
      throw invalid_argument(fieldName + " 값이 비어 있습니다.");
    }

    size_t pos = 0;
    double result = 0.0;

    try
    {
      result = stod(trimmed, &pos);
    }
    catch (const exception &)
    {
      throw invalid_argument(fieldName + " 값은 숫자여야 합니다.");
    }

    if (pos != trimmed.size())
    {
      throw invalid_argument(fieldName + " 값에 숫자가 아닌 문자가 포함되어 있습니다.");
    }

    return result;
  }
}

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
  string userIdToken, movieIdToken, scoreToken, extra;

  if (!getline(ss, userIdToken, ',') ||
      !getline(ss, movieIdToken, ',') ||
      !getline(ss, scoreToken, ','))
  {
    throw invalid_argument("평점 CSV 컬럼 수가 부족합니다.");
  }

  if (getline(ss, extra, ','))
  {
    throw invalid_argument("평점 CSV 컬럼 수가 너무 많습니다.");
  }

  int userId = parseIntStrict(userIdToken, "사용자 ID");
  int movieId = parseIntStrict(movieIdToken, "영화 ID");
  double score = parseDoubleStrict(scoreToken, "평점");

  if (userId <= 0)
  {
    throw invalid_argument("사용자 ID는 1 이상이어야 합니다.");
  }

  if (movieId <= 0)
  {
    throw invalid_argument("영화 ID는 1 이상이어야 합니다.");
  }

  if (!Rating::isValidScore(score))
  {
    throw invalid_argument("평점은 0.0 이상 5.0 이하이어야 합니다.");
  }

  ratings.push_back(Rating(userId, movieId, score));
}

string RatingManager::getHeader() const
{
  return "userId,movieId,score";
}

string RatingManager::formatLine(int index) const
{
  stringstream ss;
  ss << ratings[index].getUserId() << ","
     << ratings[index].getMovieId() << ","
     << ratings[index].getScore();

  return ss.str();
}