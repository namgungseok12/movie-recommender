#pragma once
#include <string>
#include <vector>
#include "Movie.h"
#include "Rating.h"

class MovieManager;
class UserManager;
class RatingManager;

// 이웃 기반 협업 필터링(Collaborative Filtering) 알고리즘을 수행
class Recommender
{
private:
    const MovieManager &movieManager;
    const UserManager &userManager;
    const RatingManager &ratingManager;

public:
    Recommender(const MovieManager &movieMgr, const UserManager &userMgr, const RatingManager &ratingMgr);

    // 두 사용자의 평점 벡터를 비교하여 유사도 점수를 정수로 계산
    static int Similaritycalculate(const std::vector<Rating> &ratingsA, const std::vector<Rating> &ratingsB);

    // 기존 추천 함수
    std::vector<Movie> recommend(const std::string &userName, int k, int n) const;

    // 추천 실패 이유 반환 함수
    std::vector<Movie> recommend(const std::string &userName, int k, int n, std::string &reason) const;
};