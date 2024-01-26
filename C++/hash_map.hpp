#pragma once

#include <iostream>
#include "vector.hpp"
#include "deque.hpp"

template <typename K, typename V, typename H = std::hash<K>>
class Hash_Map {
  private:
    // Inner class representing key-value pairs
    class Pair {
      public:
        K key;
        V value;

        Pair(K k) : key(k), value(V()) { }
        Pair(K k, V v) : key(k), value(v) { }
    };

  private:
    Vector<Deque<Pair>> table;  // Storage for key-value pairs
    size_t current_size;        // Current number of elements
    size_t hm_capacity;         // Total capacity
    H hasher;                   // Hash function

  public:
    // Constructors
    Hash_Map(size_t initial_capacity = 16);
    Hash_Map(size_t initial_capacity, std::initializer_list<Pair> initList = {});
    Hash_Map(std::initializer_list<Pair> initList = {});
    Hash_Map(const Hash_Map& other);
    Hash_Map(Hash_Map&& other);

    // Assignment operators
    Hash_Map& operator=(const Hash_Map& other);
    Hash_Map& operator=(Hash_Map&& other);

    // Accessors
    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    // Element access operators
    V& operator[](const K& k);
    const V& operator[](const K& k) const;

    // Modifiers
    void insert(const K& k, const V& v);
    void remove(const K& k);
    void clear();

    // Capacity control
    void rehash(size_t new_capacity);

    // Lookup
    const V& get(const K& k) const;  // Get the value associated with the key
    bool contains(const K& k) const; // Check if the key is present

  private:
    // Inner iterator class
    class iterator {
      public:
        iterator();

        // Increment and decrement operators
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        // Comparison operators
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

        // Dereference operator
        Pair& operator*() const;
    };

  public:
    // Iterator accessors
    iterator begin();
    iterator end();
};
