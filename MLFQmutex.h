#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include <chrono>
#include <vector>
#include <random>
#include <stdio.h>
#include <unistd.h>
#include <unordered_map>
#include <atomic>
#include "queue.h"
#include "park.h"

using namespace std;

class MLFQMutex {
private:
    Garage garage;
    vector<Queue<pthread_t>> levels;
    unordered_map<pthread_t, int> thread_level;
    double quantum;
    double timer;
    int flag;
    atomic_flag guard;

public:
    MLFQMutex(int num_levels, double quantum);
    void lock();
    void unlock();
    void print();
};
