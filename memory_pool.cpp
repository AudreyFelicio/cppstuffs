#include <iostream>
#include <vector>

template <typename T>
class MemoryPool {
public:
  MemoryPool(std::size_t capacity): free_memory(capacity, nullptr) {
    buffer = reinterpret_cast<T*>(malloc(sizeof(T) * capacity));
    for (size_t i = 0; i < capacity; ++i) {
      free_memory[i] = buffer + i;
    }
  }

  MemoryPool(const MemoryPool& pool) = delete;

  MemoryPool& operator=(const MemoryPool& pool) = delete;

  MemoryPool(MemoryPool&& pool) = delete;
  
  MemoryPool& operator=(MemoryPool&& pool) = delete;

  ~MemoryPool() {
    free(buffer);
  }

  T* allocate() {
    T* memory = free_memory.back();
    free_memory.pop_back();
    return memory;
  }

  void deallocate(T* ptr) {
    ptr->~T();
    free_memory.push_back(ptr);
  }

  void printPool() {
  }

private:
  T* buffer;
  std::vector<T*> free_memory;
};

int main() {
  MemoryPool<int> pool(3);
  int* five = new(pool.allocate()) int(5);
  pool.deallocate(five);
}
