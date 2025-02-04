<!-- # Multi Level Feedback Queue for Mutex Locks -->
# Mutex Locks with Multi Level Feedback Queue

This project is a simulation of a multi-level feedback queue for mutex locks. The project is implemented in C++ and uses the pthread library for thread management. The project is implemented in a Linux environment. 

MLFQ is usually used in CPU scheduling algorithms to penalize processes that use too much CPU time. In this project, we use MLFQ to implement a Mutex lock that penalize threads that held the mutex lock for too long in previous uses.

## How to run the project

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