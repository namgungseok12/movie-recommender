#pragma once
#include <vector>
#include <string>
#include "BaseManager.h"
#include "Movie.h"

class RatingManager;

class MovieManager : public BaseManager
{
private:
  std::vector<Movie> movies;
  int nextMovieId;

public:
  MovieManager();

  int addMovie(const std::string &title, const std::string &genre, int year);
  const Movie *findByTitle(const std::string &title) const;
  const Movie *findById(int id) const; 

  void printAllSortedByTitle(const RatingManager &ratingManager) const;
  void printAllSortedByRating(const RatingManager &ratingManager) const;

  // BaseManager 인터페이스 구현
  void loadFromFile(const std::string &filename) override;
  void saveToFile(const std::string &filename) const override;
  int size() const override;
};