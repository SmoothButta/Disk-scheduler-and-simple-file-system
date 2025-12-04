#include "DiskScheduler.h"
#include <algorithm>
#include <cmath>
#include <vector>

DiskScheduler::DiskScheduler(int diskSize_, int initialHead)
    : requests(), diskSize(diskSize_), head(initialHead) { }

void DiskScheduler::addRequest(int track) {
    // Optionally validate: if (track < 0 || track >= diskSize) ignore or clamp
    requests.push_back(track);
}

int DiskScheduler::runFCFS() {
    int total = 0;
    int current = head;
    for (int r : requests) {
        total += std::abs(r - current);
        current = r;
    }
    return total;
}

int DiskScheduler::runSSTF() {
    int total = 0;
    int current = head;
    std::vector<int> pending = requests;
    while (!pending.empty()) {
        auto it = std::min_element(pending.begin(), pending.end(),
            [current](int a, int b) { return std::abs(a - current) < std::abs(b - current); });
        total += std::abs(*it - current);
        current = *it;
        pending.erase(it);
    }
    return total;
}

int DiskScheduler::runSCAN() {
    // Elevator: go towards one end (right/up), then reverse to other end.
    int total = 0;
    int current = head;
    std::vector<int> left, right;

    for (int r : requests) {
        if (r < current) left.push_back(r);
        else right.push_back(r);
    }

    std::sort(left.begin(), left.end());   // ascending
    std::sort(right.begin(), right.end()); // ascending

    // Move rightwards to the end servicing requests
    for (int r : right) {
        total += std::abs(r - current);
        current = r;
    }

    // If there were requests on the left, go to the end (max track) and reverse
    if (!left.empty()) {
        // move from current to disk end (diskSize - 1)
        total += std::abs((diskSize - 1) - current);
        current = diskSize - 1;
        // service left requests from largest to smallest
        for (auto it = left.rbegin(); it != left.rend(); ++it) {
            total += std::abs(*it - current);
            current = *it;
        }
    }

    return total;
}

int DiskScheduler::runCSCAN() {
    // Circular SCAN: service to the right until end, jump to start, continue
    int total = 0;
    int current = head;
    std::vector<int> left, right;

    for (int r : requests) {
        if (r < current) left.push_back(r);
        else right.push_back(r);
    }

    std::sort(left.begin(), left.end());   // ascending
    std::sort(right.begin(), right.end()); // ascending

    // Service right side
    for (int r : right) {
        total += std::abs(r - current);
        current = r;
    }

    if (!left.empty()) {
        // move to the end
        total += std::abs((diskSize - 1) - current);
        // wrap from end to start (simulate jump)
        total += (diskSize - 1); // cost of jump (could be considered zero in some models, but we account distance)
        current = 0;
        // service left side from smallest to largest
        for (int r : left) {
            total += std::abs(r - current);
            current = r;
        }
    }

    return total;
}

int DiskScheduler::runLOOK() {
    // Like SCAN but does not go to disk ends; it reverses at the last request.
    int total = 0;
    int current = head;
    std::vector<int> left, right;

    for (int r : requests) {
        if (r < current) left.push_back(r);
        else right.push_back(r);
    }

    std::sort(left.begin(), left.end());   // ascending
    std::sort(right.begin(), right.end()); // ascending

    // go right first
    for (int r : right) {
        total += std::abs(r - current);
        current = r;
    }

    // then go back left from the largest left request downwards
    for (auto it = left.rbegin(); it != left.rend(); ++it) {
        total += std::abs(*it - current);
        current = *it;
    }

    return total;
}

int DiskScheduler::runCLOOK() {
    // Like C-SCAN but only jumps between the last request on the right and the first request on the left
    int total = 0;
    int current = head;
    std::vector<int> left, right;

    for (int r : requests) {
        if (r < current) left.push_back(r);
        else right.push_back(r);
    }

    std::sort(left.begin(), left.end());   // ascending
    std::sort(right.begin(), right.end()); // ascending

    // service right
    for (int r : right) {
        total += std::abs(r - current);
        current = r;
    }

    if (!left.empty()) {
        // jump from current (last right-served) to left.front() (smallest left)
        total += std::abs(current - left.front());
        current = left.front();
        // then serve the remaining left requests in ascending order
        for (size_t i = 1; i < left.size(); ++i) {
            total += std::abs(left[i] - current);
            current = left[i];
        }
    }

    return total;
}
