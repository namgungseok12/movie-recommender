#include "MovieManager.h"
#include "RatingManager.h"
#include <iostream>
#include <algorithm>

using namespace std;


  void printMovieWithRating(const Movie &movie, const RatingManager &ratingManager)
  {
    cout << movie
         << " | 평균 평점: " << ratingManager.getAverageRatingByMovieId(movie.getId())
         << " (" << ratingManager.getRatingCountByMovieId(movie.getId()) << "건)";
  }


MovieManager::MovieManager() : nextMovieId(1)
{
}

int MovieManager::addMovie(const std::string &title, const std::string &genre, int year)
{
  Movie newMovie(nextMovieId, title, genre, year);

  for (const Movie &movie : movies)
  {
    if (movie == newMovie)
    {
      cout << "이미 같은 제목의 영화가 존재합니다. 추가되지 않았습니다." << endl;
      return -1;
    }
  }

  movies.push_back(newMovie);

  int createdId = nextMovieId;
  nextMovieId++;
  return createdId;
}

Movie *MovieManager::findByTitle(const string &title)
{
  Movie target(0, title, "", 0);

  for (Movie &movie : movies)
  {
    if (movie == target)
    {
      return &movie;
    }
  }

  return nullptr;
}

void MovieManager::printAllSortedByTitle(const RatingManager &ratingManager) const
{
  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  vector<Movie> sortedMovies = movies;
  sort(sortedMovies.begin(), sortedMovies.end());

  for (const Movie &movie : sortedMovies)
  {
    printMovieWithRating(movie, ratingManager);
    cout << endl;
  }
}

void MovieManager::printAllSortedByRating(const RatingManager &ratingManager) const
{
  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  vector<Movie> sortedMovies = movies;
  sort(sortedMovies.begin(), sortedMovies.end(),
       [&ratingManager](const Movie &a, const Movie &b)
       {
         const double avgA = ratingManager.getAverageRatingByMovieId(a.getId());
         const double avgB = ratingManager.getAverageRatingByMovieId(b.getId());

         if (avgA != avgB)
         {
           return avgA > avgB;
         }
         return a.getTitle() < b.getTitle();
       });

  for (const Movie &movie : sortedMovies)
  {
    printMovieWithRating(movie, ratingManager);
    cout << endl;
  }
}