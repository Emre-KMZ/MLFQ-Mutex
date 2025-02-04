#include "park.h"

Garage::Garage() = default;

Garage::~Garage() = default;

void Garage::setPark() {
    pthread_t current_id = pthread_self();
    flag_map[current_id] = false;
}

void Garage::park() {
    pthread_t current_id = pthread_self();
    flag_map[current_id].wait(false);
}

void Garage::unpark(pthread_t id) {
    auto it = flag_map.find(id);
    if (it != flag_map.end()) {
        it->second.store(true);
        it->second.notify_one();
    }
}
