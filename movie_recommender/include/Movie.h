#pragma once
#include <string>
#include <iostream>

// 영화 데이터를 보관 클래스
class Movie
{
private:
  int id;            // 영화 고유 ID
  std::string title; // 영화 제목
  std::string genre; // 영화 장르
  int releaseYear;   // 개봉 연도

public:
  Movie();
  Movie(int id, const std::string &title, const std::string &genre, int year);

  int getId() const;
  std::string getTitle() const;
  std::string getGenre() const;
  int getReleaseYear() const;

  // 개봉 연도 유효성 검증 함수 (1888년 최초 영화 등장 ~ 2100년 제한)
  static bool isValidYear(int year);

  // 연산자 오버로딩
  bool operator==(const Movie &other) const;
  bool operator<(const Movie &other) const;
  friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
};