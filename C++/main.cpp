#include "deque.hpp"
#include <chrono>
#include <iomanip>
#include <stdexcept>
#include "vector.hpp"

bool test_deque() {
  int intArr[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
  auto intDeque_ptr = new Deque<int>;
  if (!intDeque_ptr->empty()) { return false; }
  intDeque_ptr->push_front(intArr[2]);
  intDeque_ptr->push_front(intArr[1]);
  intDeque_ptr->push_front(intArr[0]);
  intDeque_ptr->push_back(intArr[3]);
  intDeque_ptr->push_back(intArr[4]);
  intDeque_ptr->push_back(intArr[5]);
  intDeque_ptr->push_front(0);
  intDeque_ptr->push_back(intArr[6]);
  intDeque_ptr->push_back(intArr[7]);
  intDeque_ptr->push_back(intArr[8]);
  if (intDeque_ptr->empty()) { return false; }

  if (intDeque_ptr->pop_front()) { return false; }

  size_t i = 0;
  auto it = intDeque_ptr->getHead();
  while (it) {
    if (it->value != intArr[i++]) return false;
    it = it->next;
  }

  size_t j = sizeof(intArr) / sizeof(intArr[0]);
  while (intDeque_ptr->getTail()) {
    if (intDeque_ptr->pop_back() != intArr[--j]) return false;
  }

  return intDeque_ptr->empty();
}

double benchmark_deque(size_t num_tests, size_t num_iterations) {
  double total_time = 0;
  size_t test_iter, i;

  for (test_iter = 0; test_iter < num_tests; ++test_iter) {
    auto start = std::chrono::high_resolution_clock::now();
    Deque<int> deque;

    for (i = 0; i < num_iterations; ++i) {
      deque.push_front(i);
    }

    for (i = 0; i < num_iterations; ++i) {
      deque.front();
      deque.pop_back();
    }

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
    total_time += duration;
  }

  return total_time / num_tests;
}

void run_deque() {
  std::cout << (test_deque() ? "Deque passed in every test made." : "Deque failed in at least one test.") << std::endl;
  size_t tests = 50;
  size_t its = 1000000;
  std::cout << benchmark_deque(tests, its) << " milliseconds taken to push and pop " << its << " ints from my Deque" << std::endl;
}

int main(void) {
  Vector<int> v = { 8, 4, 5, 9 };

  v.push_back(6);
  v.push_back(9);

  v[2] = -1;

  // for (size_t i = 0; i < v.size(); i++)
  for (auto n : v)
    std::cout << n << ' ';
  std::cout << '\n';

  return 0;
}
