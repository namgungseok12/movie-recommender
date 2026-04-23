#include "Movie.h"

Movie::Movie()
    : id(0), title(""), genre(""), releaseYear(0)
{
}

Movie::Movie(int id, const std::string &title, const std::string &genre, int year)
    : id(id), title(title), genre(genre), releaseYear(year)
{
}

int Movie::getId() const
{
    return id;
}

std::string Movie::getTitle() const
{
    return title;
}

std::string Movie::getGenre() const
{
    return genre;
}

int Movie::getReleaseYear() const
{
    return releaseYear;
}

bool Movie::isValidYear(int year)
{
    return year >= 1888 && year <= 2100;
}

bool Movie::operator==(const Movie &other) const
{
    return title == other.title;
}

bool Movie::operator<(const Movie &other) const
{
    return title < other.title;
}

std::ostream &operator<<(std::ostream &os, const Movie &movie)
{
    os << "[ID: " << movie.id << "] "
       << movie.title
       << " (" << movie.releaseYear << ")"
       << " | 장르: " << movie.genre;
    return os;
}