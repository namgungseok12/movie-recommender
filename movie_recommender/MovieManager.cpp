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
  std::sort(movies.begin(), movies.end(),
            [](const Movie &a, const Movie &b)
            {
              if (a.getAverageRating() != b.getAverageRating())
              {
                return a.getAverageRating() > b.getAverageRating();
              }
              return a.getTitle() < b.getTitle();
            });
}

void MovieManager::printAll() const
{
  for (const Movie &movie : movies)
  {
    movie.display();
  }
}