CXX = g++
CXXFLAGS = -Wall -g -O2 -Ilogger -Igui -Ichunk -Iinput
SRCS = $(wildcard  logger/*.cpp main.cpp gui/windows/*.cpp gui/components/*.cpp chunk/*.cpp input/*.cpp )
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))

TARGET = build/PixBrush

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lraylib -lrimgui


build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean