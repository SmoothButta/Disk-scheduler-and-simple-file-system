# Disk-scheduler-and-simple-file-system
# Disk Scheduler and Simple File System Simulator

This project simulates disk scheduling algorithms and implements a simple file system with indexed allocation.

## Features

### Disk Scheduler
- Algorithms implemented: FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK
- Tracks total disk head movement for a sequence of I/O requests
- Configurable disk size and initial head position

### File System
- Flat directory structure
- Indexed block allocation
- Basic file operations: create, delete, read, write

### Testing
- Unit tests for both disk scheduler and file system included
- Runs on FreeBSD 

## Build and Run

### Requirements
- C++ compiler 
- FreeBSD

### Build Simulator
```bash
make
./disk_simulator
