#include "MovieManager.h"
#include "RatingManager.h"
#include "Timer.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <stdexcept>
#include <cctype>

using namespace std;

namespace
{
  string formatRating(double score)
  {
    stringstream ss;
    ss << fixed << setprecision(1) << score;
    return "⭐" + ss.str();
  }

  string trim(const string &str)
  {
    size_t start = str.find_first_not_of(" \t\r\n");
    if (start == string::npos)
    {
      return "";
    }

    size_t end = str.find_last_not_of(" \t\r\n");
    return str.substr(start, end - start + 1);
  }

  int parseIntStrict(const string &value, const string &fieldName)
  {
    string trimmed = trim(value);

    if (trimmed.empty())
    {
      throw invalid_argument(fieldName + " 값이 비어 있습니다.");
    }

    size_t pos = 0;
    int result = 0;

    try
    {
      result = stoi(trimmed, &pos);
    }
    catch (const exception &)
    {
      throw invalid_argument(fieldName + " 값은 정수여야 합니다.");
    }

    if (pos != trimmed.size())
    {
      throw invalid_argument(fieldName + " 값에 숫자가 아닌 문자가 포함되어 있습니다.");
    }

    return result;
  }

  void printMovieWithRating(const Movie &movie, const RatingManager &ratingManager)
  {
    double avg = ratingManager.getAverageRatingByMovieId(movie.getId());

    cout << movie
         << " | 평점: " << formatRating(avg)
         << " (" << ratingManager.getRatingCountByMovieId(movie.getId()) << "건)";
  }

  void printMovieWithCachedRating(const Movie &movie, double averageRating, int ratingCount)
  {
    cout << movie
         << " | 평점: " << formatRating(averageRating)
         << " (" << ratingCount << "건)";
  }

  struct MovieRatingInfo
  {
    const Movie *movie;
    double averageRating;
    int ratingCount;
  };
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
  for (const Movie &movie : movies)
  {
    if (movie.getId() == id)
    {
      return &movie;
    }
  }
  return nullptr;
}

const vector<Movie> &MovieManager::getMovies() const
{
  return movies;
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
  Perf::Timer timer("MovieManager::printAllSortedByRating");

  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  vector<MovieRatingInfo> sortedMovies;
  sortedMovies.reserve(movies.size());

  for (const Movie &movie : movies)
  {
    sortedMovies.push_back({
        &movie,
        ratingManager.getAverageRatingByMovieId(movie.getId()),
        ratingManager.getRatingCountByMovieId(movie.getId())});
  }

  sort(sortedMovies.begin(), sortedMovies.end(),
       [](const MovieRatingInfo &a, const MovieRatingInfo &b)
       {
         if (a.averageRating != b.averageRating)
         {
           return a.averageRating > b.averageRating;
         }
         return a.movie->getTitle() < b.movie->getTitle();
       });

  for (const MovieRatingInfo &info : sortedMovies)
  {
    printMovieWithCachedRating(*info.movie, info.averageRating, info.ratingCount);
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
  string idToken, title, genre, yearToken, extra;

  if (!getline(ss, idToken, ',') ||
      !getline(ss, title, ',') ||
      !getline(ss, genre, ',') ||
      !getline(ss, yearToken, ','))
  {
    throw invalid_argument("영화 CSV 컬럼 수가 부족합니다.");
  }

  if (getline(ss, extra, ','))
  {
    throw invalid_argument("영화 CSV 컬럼 수가 너무 많습니다.");
  }

  int id = parseIntStrict(idToken, "영화 ID");
  int year = parseIntStrict(yearToken, "개봉 연도");

  title = trim(title);
  genre = trim(genre);

  if (id <= 0)
  {
    throw invalid_argument("영화 ID는 1 이상이어야 합니다.");
  }

  if (title.empty())
  {
    throw invalid_argument("영화 제목이 비어 있습니다.");
  }

  if (genre.empty())
  {
    throw invalid_argument("장르가 비어 있습니다.");
  }

  if (!Movie::isValidYear(year))
  {
    throw invalid_argument("개봉 연도 범위가 올바르지 않습니다.");
  }

  movies.push_back(Movie(id, title, genre, year));
}

void MovieManager::onPostLoad()
{
  int maxId = 0;

  for (const Movie &movie : movies)
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
  const Movie &m = movies[index];
  return to_string(m.getId()) + "," + m.getTitle() + "," + m.getGenre() + "," + to_string(m.getReleaseYear());
}