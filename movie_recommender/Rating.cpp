#include "Rating.h"

using namespace std;

Rating::Rating() : userId(0), movieId(0), score(0.0)
{
}

Rating::Rating(int uId, int mId, double s)
    : userId(uId), movieId(mId), score(s)
{
}

int Rating::getUserId() const
{
    return userId;
}

int Rating::getMovieId() const
{
    return movieId;
}

double Rating::getScore() const
{
    return score;
}

bool Rating::isValidScore(double score)
{
    return score >= 0.0 && score <= 5.0;
}

ostream &operator<<(ostream &os, const Rating &rating)
{
    os << "[Rating] User ID: " << rating.userId
       << " | Score: " << rating.score;
    return os;
}