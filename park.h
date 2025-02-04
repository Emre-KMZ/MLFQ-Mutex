#ifndef GARAGE_H
#define GARAGE_H

#include <iostream>
#include <mutex>
#include <atomic>
#include <unordered_map>
#include <pthread.h>

class Garage {
private:
    std::unordered_map<pthread_t, std::atomic<bool>> flag_map;

public:
    Garage();
    ~Garage();

    void setPark();
    void park();
    void unpark(pthread_t id);
};

#endif // GARAGE_H
