#pragma once
#include <vector>
#include "BaseManager.h"
#include "Rating.h"

class RatingManager : public BaseManager
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


  std::vector<Rating> findByUser(int userId) const;
  std::vector<int> getAllUserIds() const;

  // BaseManager 인터페이스 구현
  void loadFromFile(const std::string &filename) override;
  void saveToFile(const std::string &filename) const override;
  int size() const override;
};