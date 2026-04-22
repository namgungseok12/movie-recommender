#include "MovieManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool MovieManager::addMovie(const Movie &movie)
{
  for (const Movie &m : movies)
  {
    if (m == movie)
    {
      cout << "이미 같은 제목의 영화가 존재합니다. 추가되지 않았습니다." << endl;
      return false;
    }
  }

  movies.push_back(movie);
  return true;
}

Movie *MovieManager::findByTitle(const string &title)
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
  sort(movies.begin(), movies.end());
}

void MovieManager::printAll() const
{
  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  for (const Movie &movie : movies)
  {
    cout << movie << endl;
  }
}

void MovieManager::printSortedByRating() const
{
  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  vector<Movie> sortedMovies = movies;

  sort(sortedMovies.begin(), sortedMovies.end(),
       [](const Movie &a, const Movie &b)
       {
         if (a.getAverageRating() != b.getAverageRating())
         {
           return a.getAverageRating() > b.getAverageRating();
         }
         return a.getTitle() < b.getTitle();
       });

  for (const Movie &movie : sortedMovies)
  {
    cout << movie << endl;
  }
}