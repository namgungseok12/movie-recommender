#pragma once
#include <string>

class MovieManager;
class UserManager;
class RatingManager;

class Recommender
{
private:
  const MovieManager &movieManager;
  const UserManager &userManager;
  const RatingManager &ratingManager;

public:
  Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr);
  void printRecommendations(const std::string &userName) const;
};