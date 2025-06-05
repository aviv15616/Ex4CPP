# anksilae@gmail.com


CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -Iinclude
LDFLAGS =


SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

TEST_FILE = Tests.cpp
DEMO_FILE = Demo.cpp
EXEC_MAIN = $(BUILD_DIR)/main
EXEC_TEST = $(BUILD_DIR)/test

.PHONY: all clean test build-test Main valgrind gcov

all: Main test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Main: $(DEMO_FILE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC_MAIN) $(DEMO_FILE) $(LDFLAGS)
	./$(EXEC_MAIN)

build-test: $(TEST_FILE) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(EXEC_TEST) $(TEST_FILE) $(LDFLAGS)

test: build-test
	./$(EXEC_TEST)

valgrind: build-test
	valgrind --leak-check=full ./$(EXEC_TEST)

clean:
	rm -rf $(BUILD_DIR)

