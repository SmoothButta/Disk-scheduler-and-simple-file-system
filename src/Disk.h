#ifndef DISK_H
#define DISK_H

#include <vector>

struct Disk {
  int size;  //#of tracks
  std::vector<int> tracks;
  Disk(int s) : size(s), tracks(s, 0) {}
};

#endif
