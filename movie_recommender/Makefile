CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET = movie_recommender

OBJS = main.o Movie.o User.o Rating.o MovieManager.o UserManager.o RatingManager.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp Movie.h User.h Rating.h MovieManager.h UserManager.h RatingManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c Movie.cpp

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Rating.o: Rating.cpp Rating.h
	$(CXX) $(CXXFLAGS) -c Rating.cpp

MovieManager.o: MovieManager.cpp MovieManager.h Movie.h
	$(CXX) $(CXXFLAGS) -c MovieManager.cpp

UserManager.o: UserManager.cpp UserManager.h User.h
	$(CXX) $(CXXFLAGS) -c UserManager.cpp

RatingManager.o: RatingManager.cpp RatingManager.h Rating.h
	$(CXX) $(CXXFLAGS) -c RatingManager.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)