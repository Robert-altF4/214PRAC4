CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = taskforge

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)