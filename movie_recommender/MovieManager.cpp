#include "MovieManager.h"
#include <algorithm>

void MovieManager::addMovie(const Movie &movie)
{
  movies.push_back(movie);
}

Movie *MovieManager::findByTitle(const std::string &title)
{
  for (Movie &movie : movies)
  {
    if (movie.getTitle() == title)
    {
      return &movie;
    }
  }
  return nullptr;
}

void MovieManager::sortByRating()
{
  std::sort(movies.begin(), movies.end());
}

void MovieManager::printAll() const
{
  for (const Movie &movie : movies)
  {
    movie.display();
  }
}