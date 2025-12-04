#ifndef DISK_SCHEDULER_H
#DEFINE DISK_SCHEDULER_H

#include <vector>

class DiskScheduler {
public:
  DiskScheduler(int diskSize, int head);
  void addRequest(int track);
  int runFCFS();
  int runSSTF();
  int runSCAN();
  int runLOOK();
  int runCLOOK();

private:
  std::vector<int> requests;
  int diskSize;
  int head;

};

#endif
