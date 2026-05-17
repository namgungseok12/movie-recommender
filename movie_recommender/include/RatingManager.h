#pragma once
#include <vector>
#include "Rating.h"

class RatingManager
{
private:
  std::vector<Rating> ratings;

public:
  void addRating(const Rating &rating);
  void printAll() const;
  void printRatingsByMovieId(int movieId) const;
  double getAverageRatingByMovieId(int movieId) const;
  int getRatingCountByMovieId(int movieId) const;
  bool hasRating(int userId, int movieId) const;
};