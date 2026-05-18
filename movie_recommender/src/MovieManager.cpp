#include "MovieManager.h"
#include "RatingManager.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

namespace
{
  void printMovieWithRating(const Movie &movie, const RatingManager &ratingManager)
  {
    cout << movie
         << " | 평점: " << ratingManager.getAverageRatingByMovieId(movie.getId())
         << " (" << ratingManager.getRatingCountByMovieId(movie.getId()) << "건)";
  }
}

MovieManager::MovieManager() : nextMovieId(1)
{
}

int MovieManager::addMovie(const string &title, const string &genre, int year)
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

const Movie *MovieManager::findByTitle(const string &title) const
{
  Movie target(0, title, "", 0);

  for (const Movie &movie : movies)
  {
    if (movie == target)
    {
      return &movie;
    }
  }
  return nullptr;
}

const Movie *MovieManager::findById(int id) const
{
  for (const auto &movie : movies)
  {
    if (movie.getId() == id)
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
  sort(sortedMovies.begin(), sortedMovies.end(), [&ratingManager](const Movie &a, const Movie &b)
       {
            const double avgA = ratingManager.getAverageRatingByMovieId(a.getId());
            const double avgB = ratingManager.getAverageRatingByMovieId(b.getId());

            if (avgA != avgB)
            {
                return avgA > avgB;
            }
            return a.getTitle() < b.getTitle(); });

  for (const Movie &movie : sortedMovies)
  {
    printMovieWithRating(movie, ratingManager);
    cout << endl;
  }
}

int MovieManager::size() const
{
  return static_cast<int>(movies.size());
}

void MovieManager::clear()
{
  movies.clear();
}

void MovieManager::parseLine(const string &line)
{
  stringstream ss(line);
  string token;

  getline(ss, token, ',');
  int id = stoi(token);
  getline(ss, token, ',');
  string title = token;
  getline(ss, token, ',');
  string genre = token;
  getline(ss, token, ',');
  int year = stoi(token);

  movies.push_back(Movie(id, title, genre, year));
}

void MovieManager::onPostLoad()
{
  int maxId = 0;
  for (const auto &movie : movies)
  {
    if (movie.getId() > maxId)
    {
      maxId = movie.getId();
    }
  }
  nextMovieId = maxId + 1;
}

string MovieManager::getHeader() const
{
  return "id,title,genre,releaseYear";
}

string MovieManager::formatLine(int index) const
{
  const auto &m = movies[index];
  return to_string(m.getId()) + "," + m.getTitle() + "," + m.getGenre() + "," + to_string(m.getReleaseYear());
}