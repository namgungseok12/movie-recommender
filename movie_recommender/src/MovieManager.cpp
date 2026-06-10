#include "MovieManager.h"
#include "RatingManager.h"
#include "Timer.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>

using namespace std;

namespace
{
  string formatRating(double score)
  {
    stringstream ss;
    ss << fixed << setprecision(1) << score;
    return "⭐" + ss.str();
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

void MovieManager::printStatistics(const RatingManager &ratingManager) const
{
  int choice = -1;

  do
  {
    cout << "\n=== 통계 메뉴 ===" << endl;
    cout << "1. 전체 평점 평균" << endl;
    cout << "2. 장르별 평균 평점" << endl;
    cout << "3. 평점 Top 10 영화" << endl;
    cout << "0. 돌아가기" << endl;
    cout << "선택 > ";

    cin >> choice;

    if (cin.fail())
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "올바른 번호를 입력하세요." << endl;
      continue;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice)
    {
    case 1:
    {
      if (ratingManager.size() == 0)
      {
        cout << "등록된 평점이 없습니다." << endl;
        break;
      }

      double totalScore = 0.0;
      int totalCount = 0;

      for (const Movie &movie : movies)
      {
        int count = ratingManager.getRatingCountByMovieId(movie.getId());
        if (count == 0)
        {
          continue;
        }

        double avg = ratingManager.getAverageRatingByMovieId(movie.getId());
        totalScore += avg * count;
        totalCount += count;
      }

      if (totalCount == 0)
      {
        cout << "통계를 계산할 평점이 없습니다." << endl;
        break;
      }

      cout << "\n전체 평점 평균: " << formatRating(totalScore / totalCount)
           << " (총 " << totalCount << "건)" << endl;
      break;
    }

    case 2:
    {
      if (movies.empty())
      {
        cout << "등록된 영화가 없습니다." << endl;
        break;
      }

      if (ratingManager.size() == 0)
      {
        cout << "등록된 평점이 없습니다." << endl;
        break;
      }

      map<string, double> scoreSumByGenre;
      map<string, int> ratingCountByGenre;

      for (const Movie &movie : movies)
      {
        int count = ratingManager.getRatingCountByMovieId(movie.getId());
        if (count == 0)
        {
          continue;
        }

        double avg = ratingManager.getAverageRatingByMovieId(movie.getId());
        scoreSumByGenre[movie.getGenre()] += avg * count;
        ratingCountByGenre[movie.getGenre()] += count;
      }

      if (ratingCountByGenre.empty())
      {
        cout << "장르별 통계를 계산할 평점이 없습니다." << endl;
        break;
      }

      cout << "\n=== 장르별 평균 평점 ===" << endl;
      for (const auto &entry : scoreSumByGenre)
      {
        const string &genre = entry.first;
        double avg = entry.second / ratingCountByGenre[genre];

        cout << genre << " : " << formatRating(avg)
             << " (" << ratingCountByGenre[genre] << "건)" << endl;
      }
      break;
    }

    case 3:
    {
      if (movies.empty())
      {
        cout << "등록된 영화가 없습니다." << endl;
        break;
      }

      if (ratingManager.size() == 0)
      {
        cout << "등록된 평점이 없습니다." << endl;
        break;
      }

      vector<MovieRatingInfo> topMovies;
      topMovies.reserve(movies.size());

      for (const Movie &movie : movies)
      {
        int count = ratingManager.getRatingCountByMovieId(movie.getId());
        if (count == 0)
        {
          continue;
        }

        topMovies.push_back({
            &movie,
            ratingManager.getAverageRatingByMovieId(movie.getId()),
            count});
      }

      if (topMovies.empty())
      {
        cout << "평점이 등록된 영화가 없습니다." << endl;
        break;
      }

      int topN = 10;
      if (topN > static_cast<int>(topMovies.size()))
      {
        topN = static_cast<int>(topMovies.size());
      }

      partial_sort(topMovies.begin(),
                   topMovies.begin() + topN,
                   topMovies.end(),
                   [](const MovieRatingInfo &a, const MovieRatingInfo &b)
                   {
                     if (a.averageRating != b.averageRating)
                     {
                       return a.averageRating > b.averageRating;
                     }
                     if (a.ratingCount != b.ratingCount)
                     {
                       return a.ratingCount > b.ratingCount;
                     }
                     return a.movie->getTitle() < b.movie->getTitle();
                   });

      cout << "\n=== 평점 Top " << topN << " 영화 ===" << endl;
      for (int i = 0; i < topN; ++i)
      {
        cout << i + 1 << ". ";
        printMovieWithCachedRating(*topMovies[i].movie,
                                   topMovies[i].averageRating,
                                   topMovies[i].ratingCount);
        cout << endl;
      }
      break;
    }

    case 0:
      break;

    default:
      cout << "올바른 번호를 입력하세요." << endl;
      break;
    }
  } while (choice != 0);
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