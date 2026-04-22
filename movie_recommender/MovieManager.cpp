#include "MovieManager.h"
#include <iostream>
#include <algorithm>

using namespace std;

MovieManager::MovieManager() : nextMovieId(1)
{
}

int MovieManager::addMovie(const std::string &title, const std::string &genre, int year, double initialScore)
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

    newMovie.addRating(initialScore);
    movies.push_back(newMovie);

    int createdId = nextMovieId;
    nextMovieId++;
    return createdId;
}

Movie *MovieManager::findByTitle(const string &title)
{
    for (Movie &movie : movies)
    {
        if (movie.getTitle() == title)
        {
            return &movie;
        }
    }

    return nullptr;
}

void MovieManager::sortByRating()
{
    sort(movies.begin(), movies.end());
}

void MovieManager::printAll() const
{
    if (movies.empty())
    {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }

    for (const Movie &movie : movies)
    {
        cout << movie << endl;
    }
}

void MovieManager::printSortedByRating() const
{
    if (movies.empty())
    {
        cout << "등록된 영화가 없습니다." << endl;
        return;
    }

    vector<Movie> sortedMovies = movies;

    sort(sortedMovies.begin(), sortedMovies.end(),
         [](const Movie &a, const Movie &b)
         {
             if (a.getAverageRating() != b.getAverageRating())
             {
                 return a.getAverageRating() > b.getAverageRating();
             }
             return a.getTitle() < b.getTitle();
         });

    for (const Movie &movie : sortedMovies)
    {
        cout << movie << endl;
    }
}