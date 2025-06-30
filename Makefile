CXX = g++
CXXFLAGS = -Wall -g -O2 -Igui -Ichunk -Iinput
SRCS = $(wildcard main.cpp gui/windows/*.cpp gui/components/*.cpp chunk/*.cpp input/*.cpp)
OBJS = $(patsubst %.cpp, build/%.o, $(SRCS))

TARGET = build/PixBrush

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -lraylib -lrimgui -lspdlog


build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

.PHONY: all clean