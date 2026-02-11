CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -lm
TARGET = v3test
SOURCES = v3test.c v3math.c
HEADERS = v3math.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) -o $(TARGET) $(SOURCES) $(CXXFLAGS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	./$(TARGET)

.PHONY: all clean test
