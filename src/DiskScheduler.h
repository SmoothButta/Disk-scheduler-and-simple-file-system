#ifndef DISK_SCHEDULER_H
#define DISK_SCHEDULER_H

#include <vector>

class DiskScheduler {
public:
    DiskScheduler(int diskSize, int initialHead);
    void addRequest(int track);

    // Scheduling algorithms - return total head movement
    int runFCFS();
    int runSSTF();
    int runSCAN();
    int runCSCAN();
    int runLOOK();
    int runCLOOK();

private:
    std::vector<int> requests;
    int diskSize;
    int head;
};

#endif // DISK_SCHEDULER_H

