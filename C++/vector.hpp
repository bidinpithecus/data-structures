#pragma once

#include <iostream>

template <typename T>
class Vector {
  private:
    T* array;
    size_t v_size;
    size_t v_capacity;

  public:
    Vector() : v_size(0), v_capacity(10) { array = new T[v_capacity]; }
    Vector(size_t initial_capacity) : v_size(0), v_capacity(initial_capacity) { array = new T[v_capacity]; }
    Vector(const Vector<T>& other) : v_size(other.v_size), v_capacity(other.v_capacity) {
      array = new T[v_capacity];
      std::copy(other.array, other.array + v_size, array);
    }
    Vector(std::initializer_list<T> initList) : v_size(initList.size()), v_capacity(v_size * 2) {
      array = new T[v_capacity];
      std::copy(initList.begin(), initList.end(), array);
    }
    Vector(Vector<T>&& other) noexcept : v_size(other.v_size), v_capacity(other.v_capacity), array(other.array) {
      other.v_size = 0;
      other.v_capacity = 0;
      other.array = nullptr;
    }

    ~Vector() { delete[] array; }

    inline T* begin() { return array; }
    inline T* end() { return array + v_size; }

    inline size_t size() const { return v_size; }
    inline size_t capacity() const { return v_capacity; }

    inline bool empty() const { return v_size == 0; }

    inline T front() const { return array[0]; }
    inline T back() const { return array[v_size - 1]; }

    inline Vector<T>& operator=(const Vector<T>& other) {
      if (this != &other) {
        delete[] array;

        v_size = other.v_size;
        v_capacity = other.v_capacity;
        array = new T[v_capacity];
        std::copy(other.array, other.array + v_size, array);
      }

      return *this;
    }

    inline Vector<T>& operator=(Vector<T>&& other) noexcept {
      if (this != &other) {
        std::swap(v_size, other.v_size);
        std::swap(v_capacity, other.v_capacity);
        std::swap(array, other.array);
      }
      return *this;
    }

    inline T& operator[](size_t index) {
      if (index >= v_size) {
        throw std::out_of_range("Index out of bounds");
      }

      return array[index];
    }

    inline void reserve(size_t new_capacity) {
      if (new_capacity > v_capacity) {
        T* newArray = new T[new_capacity];
        std::copy(begin(), end(), newArray);
        delete[] array;
        array = newArray;
        v_capacity = new_capacity;
      }
    }

    inline void shrink_to_fit() {
        if (v_size < v_capacity) {
            T* newArray = new T[v_size];
            std::copy(begin(), end(), newArray);
            delete[] array;
            array = newArray;
            v_capacity = v_size;
        }
    }

    inline void pop_back() {
      --v_size;
      array[v_size].~T();
      if (v_size == v_capacity / 2) {
        shrink_to_fit();
      }
    }

    inline void push_back(const T& value) {
      if (v_size == v_capacity) {
        v_capacity *= 2;
        reserve(v_capacity);
      }

      array[v_size++] = value;
    }

    template <typename... Args>
    void emplace_back(const Args&&... args) {
      if (v_size == v_capacity) {
        v_capacity *= 2;
        reserve(v_capacity);
      }

      array[v_size++] = T(std::forward<Args>(args)...);
    }

    inline void clear() {
      v_size = 0;
      v_capacity = 10;
      delete[] array;
      array = new T[v_capacity];
    }
};
