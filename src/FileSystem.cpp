#include "FileSystem.h"
#include <sstream>

FileSystem::FileSystem(int totalBlocks) : totalBlocks(totalBlocks), freeBlocks(totalBlocks, true) {}

int FileSystem::allocateBlock() {
    for (int i = 0; i < totalBlocks; ++i) {
        if (freeBlocks[i]) {
            freeBlocks[i] = false;
            return i;
        }
    }
    return -1; // No free block
}

bool FileSystem::createFile(const std::string& name, int size) {
    if (directory.find(name) != directory.end()) return false;
    File f; f.name = name;
    for (int i = 0; i < size; ++i) {
        int blk = allocateBlock();
        if (blk == -1) return false;
        f.blocks.push_back(blk);
    }
    directory[name] = f;
    return true;
}

bool FileSystem::deleteFile(const std::string& name) {  //deletefiles
    auto it = directory.find(name);
    if (it == directory.end()) return false;
    for (int blk : it->second.blocks) freeBlocks[blk] = true;
    directory.erase(it);
    return true;
}

bool FileSystem::writeFile(const std::string& name, const std::string& data) {
    if (directory.find(name) == directory.end()) return false;
    // Simulate writing (just record number of blocks needed)
    return true;
}

std::string FileSystem::readFile(const std::string& name) {
    if (directory.find(name) == directory.end()) return "";
    std::ostringstream os;
    os << "File " << name << " blocks: ";
    for (int blk : directory[name].blocks) os << blk << " ";
    return os.str();
}

