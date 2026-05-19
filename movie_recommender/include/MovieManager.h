#pragma once
#include "BaseManager.h"
#include "Movie.h"
#include <vector>
#include <string>

class RatingManager;

// BaseManager 추상 클래스를 상속받아 영화 데이터를 관리
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

  int size() const override;

protected:
  void clear() override;
  void parseLine(const std::string &line) override;
  void onPostLoad() override; // 로드 완료 후 최대 ID를 찾아 차기 nextMovieId를 세팅
  std::string getHeader() const override;
  std::string formatLine(int index) const override;
};