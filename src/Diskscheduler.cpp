#include "DiskScheduler.h"
#include <algorithm>
#include <cmath>

DiskScheduler::DiskScheduler(int diskSize, int head) : diskSize(diskSize), head(head) {}

void DiskScheduler::addRequest(int track) {
    requests.push_back(track);
}

int DiskScheduler::runFCFS() {
    int total = 0, current = head;
    for (int r : requests) {
        total += abs(r - current);
        current = r;
    }
    return total;
}

int DiskScheduler::runSSTF() {
    int total = 0, current = head;
    std::vector<int> pending = requests;
    while (!pending.empty()) {
        auto it = std::min_element(pending.begin(), pending.end(), 
            [current](int a, int b) { return abs(a - current) < abs(b - current); });
        total += abs(*it - current);
        current = *it;
        pending.erase(it);
    }
    return total;
}

int DiskScheduler::runSCAN() {
    int total = 0, current = head;
    std::vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int r : right) { total += abs(r - current); current = r; }
    if (!left.empty()) {
        total += abs(diskSize - 1 - current); // move to end
        current = diskSize - 1;
        for (auto it = left.rbegin(); it != left.rend(); ++it) {
            total += abs(*it - current);
            current = *it;
        }
    }
    return total;
}

int DiskScheduler::runCSCAN() {
    int total = 0, current = head;
    std::vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int r : right) { total += abs(r - current); current = r; }
    if (!left.empty()) {
        total += abs(diskSize - 1 - current) + (diskSize - 1); // wrap around
        current = 0;
        for (int r : left) {
            total += abs(r - current); current = r;
        }
    }
    return total;
}

int DiskScheduler::runLOOK() {
    int total = 0, current = head;
    std::vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int r : right) { total += abs(r - current); current = r; }
    for (auto it = left.rbegin(); it != left.rend(); ++it) {
        total += abs(*it - current);
        current = *it;
    }
    return total;
}

int DiskScheduler::runCLOOK() {
    int total = 0, current = head;
    std::vector<int> left, right;
    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int r : right) { total += abs(r - current); current = r; }
    if (!left.empty()) {
        total += abs(current - left.front());
        current = left.front();
        for (size_t i = 1; i < left.size(); i++) {
            total += abs(left[i] - current);
            current = left[i];
        }
    }
    return total;
}
