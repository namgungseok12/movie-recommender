// main.cpp
#include <iostream>
#include <vector>
#include "movie.h"

int main()
{
    std::vector<Movie> movies;

    // 영화 추가 (push_back)
    movies.push_back(Movie(1, "Inception", "Sci-Fi", 2010));
    movies.push_back(Movie(2, "Parasite", "Thriller", 2019));
    movies.push_back(Movie(3, "Interstellar", "Sci-Fi", 2014));

    // 평점 추가
    movies[0].addRating(4.8);
    movies[0].addRating(4.5);
    movies[1].addRating(5.0);

    // 전체 출력 (range-based for, const 참조)
    for (const Movie &m : movies)
    {
        m.display();
    }

    std::cout << "총 " << movies.size() << "편" << std::endl;
    return 0;
}
