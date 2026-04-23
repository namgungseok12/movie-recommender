#pragma once
#include <string>
#include <iostream>

class Movie
{
private:
    int id;
    std::string title;
    std::string genre;
    int releaseYear;

public:
    Movie();
    Movie(int id, const std::string &title, const std::string &genre, int year);

    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    int getReleaseYear() const;

    static bool isValidYear(int year);

    bool operator==(const Movie &other) const;
    bool operator<(const Movie &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Movie &movie);
};