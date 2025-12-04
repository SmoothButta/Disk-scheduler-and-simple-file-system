#include <iostream>
#include "DiskScheduler.h"
#include "FileSystem.h"

int main() {
    // Disk Scheduler
    DiskScheduler scheduler(200, 50);
    scheduler.addRequest(95);
    scheduler.addRequest(180);
    scheduler.addRequest(34);
    scheduler.addRequest(119);
    scheduler.addRequest(11);

    std::cout << "FCFS Total Head Movement: " << scheduler.runFCFS() << "\n";
    std::cout << "SSTF Total Head Movement: " << scheduler.runSSTF() << "\n";
    std::cout << "SCAN Total Head Movement: " << scheduler.runSCAN() << "\n";
    std::cout << "C-SCAN Total Head Movement: " << scheduler.runCSCAN() << "\n";
    std::cout << "LOOK Total Head Movement: " << scheduler.runLOOK() << "\n";
    std::cout << "C-LOOK Total Head Movement: " << scheduler.runCLOOK() << "\n";

    // File System
    FileSystem fs(100);
    fs.createFile("file1", 5);
    fs.createFile("file2", 3);
    std::cout << fs.readFile("file1") << "\n";
    fs.deleteFile("file1");
    std::cout << fs.readFile("file1") << "\n"; // Should be empty

    return 0;
}
