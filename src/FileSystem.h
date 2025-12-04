#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

#include <string>
#include <vector>
#include <map>

struct File {
    std::string name;
    std::vector<int> blocks; // Indexed allocation
};

class FileSystem {
public:
    FileSystem(int totalBlocks);
    bool createFile(const std::string& name, int size);
    bool deleteFile(const std::string& name);
    bool writeFile(const std::string& name, const std::string& data);
    std::string readFile(const std::string& name);

private:
    int totalBlocks;
    std::vector<bool> freeBlocks;
    std::map<std::string, File> directory;
    int allocateBlock();
};

#endif
