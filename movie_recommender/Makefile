CXX = g++
CXXFLAGS = -std=c++17 -Wall -g -Iinclude
TARGET = movie_recommender

SRCDIR = src
OBJDIR = obj

OBJS = $(addprefix $(OBJDIR)/, main.o Movie.o User.o Rating.o BaseManager.o MovieManager.o UserManager.o RatingManager.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)