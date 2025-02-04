// will implement this in the header file, since it is a template class
#pragma once
#include <pthread.h>

template <typename T>
class Queue { 
    private:
        struct Node {
            T value;
            Node* next;
            Node(T v) : value(v), next(nullptr) {}
            Node() : next(nullptr) {}
        };
        Node* head;
        Node* tail;
        pthread_mutex_t head_lock;
        pthread_mutex_t tail_lock;
    public:
        Queue() {
            Node* tmp = new Node();
            head = tail = tmp;
            pthread_mutex_init(&head_lock, NULL);
            pthread_mutex_init(&tail_lock, NULL);
        }

        void enqueue(T value) {
            Node* tmp = new Node(value);
            pthread_mutex_lock(&tail_lock);
            tail->next = tmp;
            tail = tmp;
            pthread_mutex_unlock(&tail_lock);
        }

        T dequeue() {
            pthread_mutex_lock(&head_lock);
            Node* tmp = head;
            Node* new_head = tmp->next;
            if (new_head == nullptr) {
                pthread_mutex_unlock(&head_lock);
                return T();
            }
            T value = new_head->value;
            head = new_head;
            pthread_mutex_unlock(&head_lock);
            delete tmp;
            return value;
        }

        bool isEmpty() {
            bool is_empt;
            pthread_mutex_lock(&head_lock);
            is_empt = (head->next == nullptr);
            pthread_mutex_unlock(&head_lock);
            return is_empt;
        }

        void print() {
            // i this does not need to be thread safe, e.g if we enqueue while printing, we simply wont print the new value
            Node* tmp = head;
            while (tmp->next != nullptr) {
                std::cout << tmp->next->value << " ";
                tmp = tmp->next;
            }
            std::cout << std::endl;
        }

        T peek() {
            pthread_mutex_lock(&head_lock);
            Node* tmp = head->next;
            if (tmp == nullptr) {
                pthread_mutex_unlock(&head_lock);
                return T();
            }
            T value = tmp->value;
            pthread_mutex_unlock(&head_lock);
            return value;
        }

        

};