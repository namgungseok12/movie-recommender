#pragma once
#include "BaseManager.h"
#include "Rating.h"
#include <vector>

class RatingManager : public BaseManager
{
private:
  std::vector<Rating> ratings;

public:
  RatingManager();

  void addRating(const Rating &rating);
  void printAll() const;
  void printRatingsByMovieId(int movieId) const;
  double getAverageRatingByMovieId(int movieId) const;
  int getRatingCountByMovieId(int movieId) const;
  bool hasRating(int userId, int movieId) const;

  std::vector<Rating> findByUser(int userId) const;
  std::vector<int> getAllUserIds() const;

  int size() const override;

protected:
  void clear() override;
  void parseLine(const std::string &line) override;
  std::string getHeader() const override;
  std::string formatLine(int index) const override;
};