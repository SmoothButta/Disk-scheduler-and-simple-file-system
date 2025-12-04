#include <iostream>
#include <cassert>
#include "../src/FileSystem.h"

void testFileSystem() {
    FileSystem fs(10);

    // Create files
    assert(fs.createFile("file1", 3) == true);
    assert(fs.createFile("file2", 4) == true);
    assert(fs.createFile("file1", 2) == false); // duplicate

    // Check read
    std::string output = fs.readFile("file1");
    assert(output.find("file1 blocks:") != std::string::npos);

    // Delete file
    assert(fs.deleteFile("file1") == true);
    assert(fs.readFile("file1") == "");

    // Allocate more than available blocks
    assert(fs.createFile("file3", 7) == false);

    std::cout << "File System Tests Passed!\n";
}

int main() {
    testFileSystem();
    return 0;
}
