CXX?=g++
CXXFLAGS?=-O2
CXXFLAGS+=-Wall -Wextra -Isrc
LDFLAGS ?= -lraylib -ltbb

SRCS=example.cpp src/engine.cpp src/physicObjects.cpp
OBJS=$(SRCS:src/%.cpp=build/%.o)
TARGET=build/prueba

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) build/*.o
