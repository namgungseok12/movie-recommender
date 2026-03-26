# Makefile — Movie 클래스 빌드
CXX      = g++
CXXFLAGS = -std=c++17 -Wall -g
TARGET   = movie_app
OBJS     = main.o movie.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<

movie.o: Movie.cpp Movie.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean run
clean:
	rm -f $(OBJS) $(TARGET)
run: $(TARGET)
	./$(TARGET)
