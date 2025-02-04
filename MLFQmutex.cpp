#include "MLFQmutex.h"

MLFQMutex::MLFQMutex(int num_levels, double quantum) {
    guard.clear();
    levels = vector<Queue<pthread_t>>(num_levels);
    this->quantum = quantum;
    timer = 0;
    flag = 0;
}

void MLFQMutex::lock() {
    cout.flush();
    while (atomic_flag_test_and_set(&guard)) {}

    if (flag == 0) { 
        // Take the lock and start the timer
        flag = 1;
        guard.clear();
        timer = chrono::duration_cast<chrono::milliseconds>(
                    chrono::system_clock::now().time_since_epoch()
                ).count(); 
        return;
    } else {
        cout.flush();
        pthread_t pid = pthread_self();

        if (thread_level.find(pid) == thread_level.end()) { 
            // If the thread is not in the map, set its level to 0
            thread_level[pid] = 0;
            levels[0].enqueue(pid);
            printf("Adding thread with ID: %ld to level %d\n", pthread_self(), 0);
        } else {
            int current_level = thread_level[pid];
            levels[current_level].enqueue(pid);
            printf("Adding thread with ID: %ld to level %d\n", pthread_self(), current_level);
        }

        garage.setPark();
        guard.clear();
        garage.park();
    }
}

void MLFQMutex::unlock() {
    while (atomic_flag_test_and_set(&guard)) {}

    double time_diff = chrono::duration_cast<chrono::milliseconds>(
                           chrono::system_clock::now().time_since_epoch()
                       ).count() - timer;

    if (thread_level.find(pthread_self()) == thread_level.end()) { 
        thread_level[pthread_self()] = 0;
    }

    int new_level = min(
        int(thread_level[pthread_self()] + floor(time_diff / (1000 * quantum))), 
        int(levels.size()) - 1
    );
    thread_level[pthread_self()] = new_level;

    bool all_empty = true;
    for (int i = 0; i < levels.size(); i++) {
        if (!levels[i].isEmpty()) {
            all_empty = false;
            break;
        }
    }

    if (all_empty) {
        flag = 0;
    } else {
        int first_level = 0;

        for (int i = 0; i < levels.size(); i++) {
            if (!levels[i].isEmpty()) {
                first_level = i;
                break;
            }
        }    
        garage.unpark(levels[first_level].dequeue());  
    }

    guard.clear();
}

void MLFQMutex::print() {
    cout << "Waiting threads: " << endl;
    for (int i = 0; i < levels.size(); i++) {
        cout << "Level " << i << ": ";
        if (levels[i].isEmpty()) {
            cout << "Empty";
        }
        levels[i].print();
    }
}
