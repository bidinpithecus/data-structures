#pragma once

#include <iostream>

template <typename T>
class Deque {
  private:
    class Node {
    public:
      T value;
      Node* prev;
      Node* next;

      Node(T value) : value(value), prev(nullptr), next(nullptr) {}
      Node(Node* node) : value(node->value), prev(node->prev), next(node->next) {}
      ~Node() { }
    };

    Node* head;
    Node* tail;
    size_t size;

  public:
    Deque() : head(nullptr), tail(nullptr), size(0) {}
    ~Deque() { clear(); }

    inline bool empty() const { return this->size == 0; }
    inline size_t getSize() const { return this->size; }
    inline Node* getHead() const { return this->head; }
    inline Node* getTail() const { return this->tail; }

    inline T& front() {
      if (empty()) { throw std::out_of_range("Deque is empty"); }
      return this->head->value;
    }

    inline const T& front() const {
      if (empty()) { throw std::out_of_range("Deque is empty"); }
      return this->head->value;
    }

    inline T& back() {
      if (empty()) { throw std::out_of_range("Deque is empty"); }
      return this->tail->value;
    }

    inline const T& back() const {
      if (empty()) { throw std::out_of_range("Deque is empty"); }
      return this->tail->value;
    }

    inline void push_front(const T& value) {
      Node* temp(new Node(value));

      temp->next = this->head;
      if (this->head != nullptr) {
        this->head->prev = temp;
      }
      this->head = temp;

      if (this->tail == nullptr) {
        this->tail = this->head;
      }

      this->size++;
    }

    inline void push_back(const T& value) {
      Node* temp(new Node(value));

      temp->prev = this->tail;
      if (this->tail != nullptr) {
        this->tail->next = temp;
      }
      this->tail = temp;

      if (this->head == nullptr) {
        this->head = this->tail;
      }

      this->size++;
    }

    inline const T pop_front() {
      if (this->empty()) {
        throw std::out_of_range("Deque is empty");
      }

      T value = this->head->value;
      Node* temp = this->head;
      this->head = temp->next;

      if (this->head) {
        this->head->prev = nullptr;
      } else {
        this->tail = nullptr;
      }

      this->size--;
      delete temp;
      return value;
    }

    inline const T pop_back() {
      if (this->empty()) {
        throw std::out_of_range("Deque is empty");
      }

      T value = this->tail->value;
      Node* temp = this->tail;
      this->tail = temp->prev;

      if (this->tail) {
        this->tail->next = nullptr;
      } else {
        this->head = nullptr;
      }

      this->size--;
      delete temp;
      return value;
    }

    inline void clear() {
      while (this->head != nullptr) {
        Node* current = this->head;
        while (current != nullptr) {
          Node* next = current->next;
          delete current;
          current = next;
        }
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
      }
    }
};
