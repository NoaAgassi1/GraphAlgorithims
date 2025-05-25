# ------------------------ COMPILER AND FLAGS ------------------------
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

# ------------------------ FOLDERS ------------------------
SRC_DIR = src
DS_DIR = src/DataStructures
TEST_DIR = tests

# ------------------------ TARGET NAMES ------------------------
TARGET = graph_program
TEST_TARGET_DS = test_data_structures_run
TEST_TARGET_ALGO = test_algorithms_run

# ------------------------ SOURCE FILES ------------------------
SRC_FILES = $(SRC_DIR)/graph.cpp $(SRC_DIR)/Algorithms.cpp \
            $(DS_DIR)/Queue.cpp $(DS_DIR)/PriorityQueue.cpp $(DS_DIR)/UnionFind.cpp \
            $(DS_DIR)/Stack.cpp


MAIN_FILE = main.cpp
TEST_FILE_DS = $(TEST_DIR)/test_data_structures.cpp
TEST_FILE_ALGO = $(TEST_DIR)/test_algorithms.cpp

# ------------------------ RULES ------------------------

all: $(TARGET)

$(TARGET): $(SRC_FILES) $(MAIN_FILE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC_FILES) $(MAIN_FILE)

$(TEST_TARGET_DS): $(SRC_FILES) $(TEST_FILE_DS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET_DS) $(SRC_FILES) $(TEST_FILE_DS)

$(TEST_TARGET_ALGO): $(SRC_FILES) $(TEST_FILE_ALGO)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET_ALGO) $(SRC_FILES) $(TEST_FILE_ALGO)

# ------------------------ SHORTCUTS ------------------------

Main: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET_DS) $(TEST_TARGET_ALGO) 
	./$(TEST_TARGET_DS) --success
	./$(TEST_TARGET_ALGO) --success

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)


clean:
	rm -f $(TARGET) $(TEST_TARGET_DS) $(TEST_TARGET_ALGO)
