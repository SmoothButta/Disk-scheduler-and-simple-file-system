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
FS_BIN   = $(BIN_DIR)/file_system
DS_TEST  = $(BIN_DIR)/test_diskscheduler
FS_TEST  = $(BIN_DIR)/test_filesystem

# Object files
DISK_SCHED_OBJ = $(OBJ_DIR)/DiskScheduler.o
DISK_OBJ       = $(OBJ_DIR)/Disk.o
FS_OBJ         = $(OBJ_DIR)/FileSystem.o
MAIN_OBJ       = $(OBJ_DIR)/main.o

# Default build
all: setup $(DISK_BIN) $(FS_BIN)

# Create directories
setup:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# ---------------- Executables ----------------
$(DISK_BIN): $(DISK_OBJ) $(DISK_SCHED_OBJ)
	$(CXX) $(CXXFLAGS) -o $(DISK_BIN) $(DISK_OBJ) $(DISK_SCHED_OBJ)

$(FS_BIN): $(FS_OBJ) $(MAIN_OBJ) $(DISK_SCHED_OBJ) $(DISK_OBJ)
	$(CXX) $(CXXFLAGS) -o $(FS_BIN) $(FS_OBJ) $(MAIN_OBJ) $(DISK_SCHED_OBJ) $(DISK_OBJ)

# ---------------- Object files ----------------
$(OBJ_DIR)/DiskScheduler.o: $(SRC_DIR)/DiskScheduler.cpp $(SRC_DIR)/DiskScheduler.h $(SRC_DIR)/Disk.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/DiskScheduler.cpp -o $(OBJ_DIR)/DiskScheduler.o

$(OBJ_DIR)/Disk.o: $(SRC_DIR)/Disk.cpp $(SRC_DIR)/Disk.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/Disk.cpp -o $(OBJ_DIR)/Disk.o

$(OBJ_DIR)/FileSystem.o: $(SRC_DIR)/FileSystem.cpp $(SRC_DIR)/FileSystem.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/FileSystem.cpp -o $(OBJ_DIR)/FileSystem.o

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/DiskScheduler.h $(SRC_DIR)/FileSystem.h
	$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $(OBJ_DIR)/main.o

# ---------------- Tests ----------------
$(DS_TEST): $(DISK_OBJ) $(DISK_SCHED_OBJ) $(TEST_DIR)/test_diskscheduler.cpp
	$(CXX) $(CXXFLAGS) -o $(DS_TEST) $(DISK_OBJ) $(DISK_SCHED_OBJ) $(TEST_DIR)/test_diskscheduler.cpp

$(FS_TEST): $(FS_OBJ) $(MAIN_OBJ) $(DISK_SCHED_OBJ) $(DISK_OBJ) $(TEST_DIR)/test_filesystem.cpp
	$(CXX) $(CXXFLAGS) -o $(FS_TEST) $(FS_OBJ) $(MAIN_OBJ) $(DISK_SCHED_OBJ) $(DISK_OBJ) $(TEST_DIR)/test_filesystem.cpp

tests: $(DS_TEST) $(FS_TEST)

test: tests
	$(DS_TEST)
	$(FS_TEST)

# ---------------- Clean ----------------
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all setup tests test clean
