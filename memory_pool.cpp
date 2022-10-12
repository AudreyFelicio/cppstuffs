#include <iostream>
#include <vector>
#include <string>

template <typename T>
class MemoryPool {
public:
  MemoryPool(size_t capacity): free_memory(capacity, nullptr) {
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

private:
  T* buffer;
  std::vector<T*> free_memory;
};

int main() {
  MemoryPool<std::string> string_pool(3);
  std::string* s1 = new(string_pool.allocate()) std::string("hello world!");
  std::string* s2 = new(string_pool.allocate()) std::string("hello world 2");
  string_pool.deallocate(s1);
}
