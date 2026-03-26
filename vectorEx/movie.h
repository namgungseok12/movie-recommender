#pragma once
#include <string>

class Movie
{
private:
  int id;
  std::string title;
  std::string genre;
  int releaseYear;
  double totalRating; // averageRating 대신
  int ratingCount;    //

public:
  Movie(); // 기본 생성자 추가
  Movie(int id, const std::string &title,
        const std::string &genre, int year);

  int getId() const;
  std::string getTitle() const;
  std::string getGenre() const;
  int getReleaseYear() const;
  double getAverageRating() const; // getRating → getAverageRating
  int getRatingCount() const;

  void addRating(double r); // 추가
  void display() const;     // const 추가
};