#pragma once

#include <vector>
#include <string>
#include "Movie.h"

class RatingManager;

class MovieManager
{
private:
  std::vector<Movie> movies;
  int nextMovieId;

public:
  MovieManager();

  int addMovie(const std::string &title, const std::string &genre, int year);
  const Movie *findByTitle(const std::string &title) const;

  void printAllSortedByTitle(const RatingManager &ratingManager) const;
  void printAllSortedByRating(const RatingManager &ratingManager) const;
};