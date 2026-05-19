#pragma once
#include "BaseManager.h"
#include "Rating.h"
#include <vector>

// BaseManager 추상 클래스를 상속받아 평점 데이터를 관리
class RatingManager : public BaseManager
{
private:
  std::vector<Rating> ratings;

public:
  RatingManager();

  void addRating(const Rating &rating);
  void printAll() const;
  void printRatingsByMovieId(int movieId) const;       // 특정 영화에 대한 평점 목록 전체 출력
  double getAverageRatingByMovieId(int movieId) const; // 특정 영화의 평균 평점 계산
  int getRatingCountByMovieId(int movieId) const;      // 특정 영화의 평점 등록 건수 조회
  bool hasRating(int userId, int movieId) const;       // 중복 평점 입력 방지

  // 추천 시스템 연동을 위한 데이터 필터링 유틸리티 함수
  std::vector<Rating> findByUser(int userId) const; // 특정 사용자가 남긴 평점 목록만 추출
  std::vector<int> getAllUserIds() const;           // 중복 없는 전체 사용자 ID 리스트 생성

  int size() const override;

protected:
  void clear() override;
  void parseLine(const std::string &line) override;
  std::string getHeader() const override;
  std::string formatLine(int index) const override; // 자동 증가 ID가 없으므로 onPostLoad는 오버라이딩 안 함
};