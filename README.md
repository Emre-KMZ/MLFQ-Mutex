<!-- # Multi Level Feedback Queue for Mutex Locks -->
# Mutex Locks with Multi Level Feedback Queue

This project simulates a multi-level feedback queue (MLFQ) for mutex locks. It is implemented in C++ and utilizes the `pthread` library for thread management in a Linux environment.  

MLFQ is typically used in CPU scheduling algorithms to penalize processes that consume excessive CPU time. In this project, we adapt MLFQ to implement a mutex lock that penalizes threads that have held the lock for too long in previous uses.  

## How to run the project

To run the project, you need to have a Linux environment with the pthread library installed. You can compile the project using the following command:
```bash
make
```
After compiling the project, you can run the tests using the following commands:
```bash
./sample1Level
./sampleMultiLevel
./sampleMultiLevelPrint
./sampleQueue
```
