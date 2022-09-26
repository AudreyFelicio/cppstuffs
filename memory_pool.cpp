#include <iostream>

template <typename T>
class MemoryPool {
public:
  MemoryPool(std::size_t capacity): capacity{capacity} {
    buffer = new T[capacity];
    is_used = new bool[capacity];
    for (std::size_t i = 0; i < capacity; ++i) {
      is_used[i] = false;
    }
  }

  ~MemoryPool() {
    delete[] buffer;
    delete[] is_used;
  }

  T* allocate() {
    for (std::size_t i = 0; i < capacity; ++i) {
      if (!is_used[i]) {
        is_used[i] = true;
        return &buffer[i];
      }
    }
    return nullptr;
  }

  void deallocate(T* ptr) {
    for (std::size_t i = 0; i < capacity; ++i) {
      if (is_used[i]) {
        buffer[i] = *ptr;
        is_used[i] = false;
        break;
      }
    }
  }

  void printPool() {
    for (std::size_t i = 0; i < capacity; ++i) {
      std::cout << buffer[i] << " ";
    }
    std::cout << std::endl;
    for (std::size_t i = 0; i < capacity; ++i) {
      std::cout << is_used[i] << " ";
    }
    std::cout << std::endl;
  }

private:
  T* buffer;
  bool* is_used;
  std::size_t capacity;
};

int main() {
  MemoryPool<int> pool(3);
  int* first = pool.allocate();
  *first = 2023;
  int* second = pool.allocate();
  *second = 2024;
  pool.printPool();
  pool.deallocate(first);
  pool.printPool();
}
