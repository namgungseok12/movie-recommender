#include "MovieManager.h"

void MovieManager::addMovie(const Movie& movie)
{
    movies.push_back(movie);
}

void MovieManager::printAll() const
{
    for (const Movie& movie : movies)
    {
        movie.display();
    }
}