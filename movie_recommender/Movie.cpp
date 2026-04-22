#include "Movie.h"

Movie::Movie()
    : id(0), title(""), genre(""), releaseYear(0), totalRating(0.0), ratingCount(0)
{
}

Movie::Movie(int id, const std::string &title, const std::string &genre, int year)
    : id(id), title(title), genre(genre), releaseYear(year), totalRating(0.0), ratingCount(0)
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

double Movie::getAverageRating() const
{
    if (ratingCount == 0)
    {
        return 0.0;
    }
    return totalRating / ratingCount;
}

int Movie::getRatingCount() const
{
    return ratingCount;
}

void Movie::addRating(double r)
{
    if (r < 0.0 || r > 5.0)
    {
        return;
    }

    totalRating += r;
    ratingCount++;
}

bool Movie::operator==(const Movie &other) const
{
    return title == other.title;
}

bool Movie::operator!=(const Movie &other) const
{
    return !(*this == other);
}

bool Movie::operator<(const Movie &other) const
{
    if (getAverageRating() != other.getAverageRating())
    {
        return getAverageRating() < other.getAverageRating();
    }
    return title < other.title;
}

std::ostream &operator<<(std::ostream &os, const Movie &movie)
{
    os << movie.id << ". " << movie.title
       << " (" << movie.releaseYear << ")"
       << "  평점: " << movie.getAverageRating()
       << " (" << movie.ratingCount << "건)";
    return os;
}