#include "RatingManager.h"
#include <iostream>

using namespace std;

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