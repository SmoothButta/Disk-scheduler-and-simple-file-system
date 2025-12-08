#include <iostream>
#include <cassert>
#include "../src/DiskScheduler.h"

void testDiskScheduler() {
    DiskScheduler scheduler(200, 50);
    scheduler.addRequest(95);
    scheduler.addRequest(180);
    scheduler.addRequest(34);
    scheduler.addRequest(119);
    scheduler.addRequest(11);

    int fcfs = scheduler.runFCFS();
    int sstf = scheduler.runSSTF();
    int scan = scheduler.runSCAN();
    int cscan = scheduler.runCSCAN();
    int look = scheduler.runLOOK();
    int clook = scheduler.runCLOOK();

    // Basic sanity checks
    assert(fcfs >= 0);
    assert(sstf >= 0);
    assert(scan >= 0);
    assert(cscan >= 0);
    assert(look >= 0);
    assert(clook >= 0);

    std::cout << "Disk Scheduler Tests Passed!\n";
    std::cout << "FCFS: " << fcfs << ", SSTF: " << sstf << ", SCAN: " << scan 
              << ", C-SCAN: " << cscan << ", LOOK: " << look << ", C-LOOK: " << clook << "\n";
}

int main() {
    testDiskScheduler();
    return 0;
}


