#include "Menu.h"
#include "MovieManager.h"
#include "UserManager.h"
#include "RatingManager.h"
#include "Recommender.h"
#include "User.h"
#include "Movie.h"
#include "Rating.h"
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <map>

using namespace std;

namespace
{
  string formatRating(double score)
  {
    stringstream ss;
    ss << fixed << setprecision(1) << score;
    return "⭐" + ss.str();
  }

  struct MovieRatingInfo
  {
    const Movie *movie;
    double averageRating;
    int ratingCount;
  };

  void printMovieWithCachedRating(const Movie &movie, double averageRating, int ratingCount)
  {
    cout << movie
         << " | 평점: " << formatRating(averageRating)
         << " (" << ratingCount << "건)";
  }
}

Menu::Menu(MovieManager &movieMgr, UserManager &userMgr, RatingManager &ratingMgr, Recommender &recom)
    : movieManager(movieMgr), userManager(userMgr), ratingManager(ratingMgr), recommender(recom)
{
}

string Menu::readLine(const string &prompt) const
{
  string input;
  cout << prompt;
  getline(cin, input);
  return input;
}

int Menu::readValidMenuChoice() const
{
  int choice;
  cin >> choice;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return -1;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

bool Menu::readValidYear(int &year) const
{
  cout << "개봉 연도 입력 (1888 ~ 2100): ";
  cin >> year;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "개봉 연도는 숫자로 입력하세요." << endl;
    return false;
  }
  if (cin.peek() != '\n')
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "유효하지 않은 연도입니다. 영화가 추가되지 않았습니다." << endl;
    return false;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (!Movie::isValidYear(year))
  {
    cout << "유효하지 않은 연도입니다. 영화가 추가되지 않았습니다." << endl;
    return false;
  }
  return true;
}

bool Menu::readValidScore(double &score, const string &invalidMessage) const
{
  cout << "평점 입력 (0.0 ~ 5.0): ";
  cin >> score;
  if (cin.fail())
  {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "평점은 숫자로 입력하세요." << endl;
    return false;
  }
  if (cin.peek() != '\n')
  {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "평점 형식이 올바르지 않습니다." << endl;
    return false;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (!Rating::isValidScore(score))
  {
    cout << invalidMessage << endl;
    return false;
  }
  return true;
}

void Menu::showOverallAverageRating() const
{
  const vector<Movie> &movies = movieManager.getMovies();

  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  if (ratingManager.size() == 0)
  {
    cout << "등록된 평점이 없습니다." << endl;
    return;
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
    return;
  }

  cout << "\n전체 평점 평균: " << formatRating(totalScore / totalCount)
       << " (총 " << totalCount << "건)" << endl;
}

void Menu::showAverageRatingByGenre() const
{
  const vector<Movie> &movies = movieManager.getMovies();

  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  if (ratingManager.size() == 0)
  {
    cout << "등록된 평점이 없습니다." << endl;
    return;
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
    return;
  }

  cout << "\n=== 장르별 평균 평점 ===" << endl;
  for (const auto &entry : scoreSumByGenre)
  {
    const string &genre = entry.first;
    double avg = entry.second / ratingCountByGenre[genre];

    cout << genre << " : " << formatRating(avg)
         << " (" << ratingCountByGenre[genre] << "건)" << endl;
  }
}

void Menu::showTopRatedMovies(int topN) const
{
  const vector<Movie> &movies = movieManager.getMovies();

  if (movies.empty())
  {
    cout << "등록된 영화가 없습니다." << endl;
    return;
  }

  if (ratingManager.size() == 0)
  {
    cout << "등록된 평점이 없습니다." << endl;
    return;
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
    return;
  }

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
}

void Menu::showStatisticsMenu() const
{
  int choice = -1;

  do
  {
    cout << "\n=== 통계 메뉴 ===" << endl;
    cout << "1. 전체 평점 평균" << endl;
    cout << "2. 장르별 평균 평점" << endl;
    cout << "3. 평점 Top 10 영화" << endl;
    cout << "0. 돌아가기" << endl;
    cout << endl;
    cout << "선택 > ";

    choice = readValidMenuChoice();

    if (choice == -1)
    {
      cout << "올바른 번호를 입력하세요." << endl;
      continue;
    }

    switch (choice)
    {
    case 1:
      showOverallAverageRating();
      break;

    case 2:
      showAverageRatingByGenre();
      break;

    case 3:
      showTopRatedMovies(10);
      break;

    case 0:
      break;

    default:
      cout << "올바른 번호를 입력하세요." << endl;
      break;
    }
  } while (choice != 0);
}

void Menu::run()
{
  int choice = -1;
  do
  {
    cout << "\n=== Movie Recommender ===" << endl;
    cout << endl
         << "[ 영화 ]" << endl;
    cout << "1. 영화 추가" << endl;
    cout << "2. 제목으로 검색" << endl;
    cout << "3. 전체 목록 출력" << endl;
    cout << "4. 평점순 정렬 출력" << endl;

    cout << endl
         << "[ 사용자 ]" << endl;
    cout << "5. 사용자 추가" << endl;
    cout << "6. 사용자 목록 출력" << endl;

    cout << endl
         << "[ 평점 ]" << endl;
    cout << "7. 평점 입력" << endl;
    cout << "8. 영화별 평점 보기" << endl;

    cout << endl
         << "[ 추천 시스템 ]" << endl;
    cout << "9. 추천 영화 보기" << endl;

    cout << endl
         << "[ 통계 ]" << endl;
    cout << "10. 통계 보기" << endl;

    cout << endl;
    cout << "0. 종료" << endl;

    cout << endl
         << "선택 > ";
    choice = readValidMenuChoice();

    if (choice == -1)
    {
      cout << "올바른 번호를 입력하세요." << endl;
      continue;
    }

    switch (choice)
    {
    case 1:
    {
      string title = readLine("영화 제목 입력: ");
      string genre = readLine("장르 입력: ");
      int year;
      if (!readValidYear(year))
        break;

      int movieId = movieManager.addMovie(title, genre, year);
      if (movieId != -1)
      {
        cout << "영화가 추가되었습니다. [ID: " << movieId << "]" << endl;
      }
      break;
    }

    case 2:
    {
      string title = readLine("검색할 영화 제목 입력: ");
      const Movie *foundMovie = movieManager.findByTitle(title);
      if (foundMovie != nullptr)
      {
        cout << "\n--- [검색 결과] ---" << endl;
        cout << *foundMovie
             << " | 평균 평점: " << formatRating(ratingManager.getAverageRatingByMovieId(foundMovie->getId()))
             << " (" << ratingManager.getRatingCountByMovieId(foundMovie->getId()) << "건)" << endl;
      }
      else
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
      }
      break;
    }

    case 3:
      cout << "\n--- [전체 영화 목록] ---" << endl;
      movieManager.printAllSortedByTitle(ratingManager);
      break;

    case 4:
      cout << "\n--- [평점순 정렬 영화 목록] ---" << endl;
      movieManager.printAllSortedByRating(ratingManager);
      break;

    case 5:
    {
      string name = readLine("사용자 이름 입력: ");
      string email = readLine("이메일 입력: ");
      int userId = userManager.addUser(name, email);
      if (userId != -1)
      {
        cout << "사용자가 추가되었습니다. [ID: " << userId << "]" << endl;
      }
      break;
    }

    case 6:
      cout << "\n--- [사용자 목록] ---" << endl;
      userManager.printAll();
      break;

    case 7:
    {
      string userName = readLine("평점을 입력할 사용자 이름 입력: ");
      const User *foundUser = userManager.findByName(userName);
      if (foundUser == nullptr)
      {
        cout << "등록된 사용자만 평점을 입력할 수 있습니다." << endl;
        break;
      }

      string movieTitle = readLine("평점을 남길 영화 제목 입력: ");
      const Movie *foundMovie = movieManager.findByTitle(movieTitle);
      if (foundMovie == nullptr)
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
        break;
      }

      if (ratingManager.hasRating(foundUser->getId(), foundMovie->getId()))
      {
        cout << "이 사용자는 이미 해당 영화에 평점을 남겼습니다." << endl;
        break;
      }

      double score;
      if (!readValidScore(score, "유효하지 않은 평점입니다. 평점이 입력되지 않았습니다."))
        break;

      Rating rating(foundUser->getId(), foundMovie->getId(), score);
      ratingManager.addRating(rating);
      cout << "평점이 입력되었습니다." << endl;
      break;
    }

    case 8:
    {
      string movieTitle = readLine("평점을 조회할 영화 제목 입력: ");
      const Movie *foundMovie = movieManager.findByTitle(movieTitle);
      if (foundMovie == nullptr)
      {
        cout << "해당 제목의 영화를 찾을 수 없습니다." << endl;
        break;
      }

      cout << "\n--- [" << movieTitle << " 평점 목록] ---" << endl;
      ratingManager.printRatingsByMovieId(foundMovie->getId());
      cout << "평균 평점: " << formatRating(ratingManager.getAverageRatingByMovieId(foundMovie->getId())) << endl;
      break;
    }

    case 9:
    {
      string userName = readLine("추천을 진행할 사용자 이름 입력: ");

      string reason;
      vector<Movie> recommendations = recommender.recommend(userName, 3, 3, reason);

      if (recommendations.empty())
      {
        cout << reason << endl;
      }
      else
      {
        cout << "\n--- [" << userName << "님 맞춤 추천 영화 목록] ---" << endl;
        for (const auto &movie : recommendations)
        {
          cout << movie << endl;
        }
      }
      break;
    }

    case 10:
      showStatisticsMenu();
      break;

    case 0:
      cout << "프로그램을 종료합니다." << endl;
      break;

    default:
      cout << "올바른 번호를 입력하세요." << endl;
      break;
    }
  } while (choice != 0);
}