#pragma once

#include <vector>
#include <string>
#include "Movie.h"

class MovieManager
{
private:
    std::vector<Movie> movies;
    int nextMovieId;

public:
    MovieManager();

    int addMovie(const std::string &title, const std::string &genre, int year, double initialScore);
    Movie *findByTitle(const std::string &title);

    void printAllSortedByTitle() const;
    void printAllSortedByRating() const;
};