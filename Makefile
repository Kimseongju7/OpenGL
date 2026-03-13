CXX = g++
TARGET = main

# macOS 내장 GLUT.framework 사용
CXXFLAGS = -Wall -Wno-deprecated
LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa

SRCS = $(wildcard *.cpp) $(wildcard *.c)
OBJS = $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
