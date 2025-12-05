# Compiler
CXX = c++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Executables
DISK_BIN = $(BIN_DIR)/disk_scheduler
FS_BIN = $(BIN_DIR)/file_system
DS_TEST = $(BIN_DIR)/test_diskscheduler
FS_TEST = $(BIN_DIR)/test_filesystem

# Source files
DISK_SRC = $(SRC_DIR)/DiskScheduler.cpp
FS_SRC = $(SRC_DIR)/FileSystem.cpp

# Object files (explicit for BSD make)
DISK_OBJ = $(OBJ_DIR)/DiskScheduler.o
FS_OBJ = $(OBJ_DIR)/FileSystem.o

# Test sources
DS_TEST_SRC = $(TEST_DIR)/test_diskscheduler.cpp
FS_TEST_SRC = $(TEST_DIR)/test_filesystem.cpp

# Default target
all: setup $(DISK_BIN) $(FS_BIN)

# Create directories
setup:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compile executables
$(DISK_BIN): $(DISK_OBJ)
	$(CXX) $(CXXFLAGS) -o $(DISK_BIN) $(DISK_OBJ)

$(FS_BIN): $(FS_OBJ)
	$(CXX) $(CXXFLAGS) -o $(FS_BIN) $(FS_OBJ)

# Compile source files to object files (explicit rules for BSD make)
$(OBJ_DIR)/DiskScheduler.o: $(SRC_DIR)/DiskScheduler.cpp $(SRC_DIR)/DiskScheduler.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/DiskScheduler.cpp -o $(OBJ_DIR)/DiskScheduler.o

$(OBJ_DIR)/FileSystem.o: $(SRC_DIR)/FileSystem.cpp $(SRC_DIR)/FileSystem.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/FileSystem.cpp -o $(OBJ_DIR)/FileSystem.o

# ---------- TESTING ----------
tests: setup $(DS_TEST) $(FS_TEST)

$(DS_TEST): $(DS_TEST_SRC) $(DISK_OBJ)
	$(CXX) $(CXXFLAGS) -o $(DS_TEST) $(DS_TEST_SRC) $(DISK_OBJ)

$(FS_TEST): $(FS_TEST_SRC) $(FS_OBJ)
	$(CXX) $(CXXFLAGS) -o $(FS_TEST) $(FS_TEST_SRC) $(FS_OBJ)

test: tests
	$(DS_TEST)
	$(FS_TEST)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all setup tests test clean
