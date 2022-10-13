#include <iostream>
#include <vector>
#include <string>
#include <cstring>

template <typename T>
class MemoryPool {
public:
  MemoryPool(size_t capacity):
    capacity(capacity),
    buffer(reinterpret_cast<T*>(malloc(sizeof(T) * capacity))),
    free_memory(reinterpret_cast<size_t*>(malloc(sizeof(size_t) * capacity))),
    next_free(nullptr) {
    for (size_t i = 0; i < capacity; ++i) {
      free_memory[i] = i;
      next_free = free_memory + i;
    }
  }

  MemoryPool(const MemoryPool& pool) = delete;

  MemoryPool& operator=(const MemoryPool& pool) = delete;

  MemoryPool(MemoryPool&& pool) = delete;
  
  MemoryPool& operator=(MemoryPool&& pool) = delete;

  ~MemoryPool() {
    free(buffer);
    free(free_memory);
  }

  T* allocate() {
    if (next_free == nullptr) {
      return nullptr;
    }
    T* memory = buffer + *next_free;
    std::cout << "allocate: " << memory << std::endl;
    if (next_free == free_memory) {
      next_free = nullptr;
    } else {
      --next_free;
    }
    return memory;
  }

  void deallocate(T* ptr) {
    std::cout << "deallocate: " << ptr << std::endl;
    if (next_free == free_memory + capacity) {
      return;
    }
    size_t curr_idx = ptr - buffer;
    ptr->~T();
    // std::cout << curr_idx << " " << ptr << " " << buffer << " " << (ptr - buffer) << std::endl;
    if (next_free == nullptr) {
      next_free = free_memory;
    } else {
      next_free++;
    }
    *next_free = curr_idx;
  }

private:
  T* buffer;
  size_t* free_memory;
  size_t* next_free;
  size_t capacity;
};

int main() {
  MemoryPool<std::string> string_pool(3);
  std::string* s1 = new(string_pool.allocate()) std::string("hello world!");
  std::string* s2 = new(string_pool.allocate()) std::string("hello world 2");
  std::string* s3 = new(string_pool.allocate()) std::string("hello world 3");
  string_pool.deallocate(s1);
  std::string* s4 = new(string_pool.allocate()) std::string("hello world 4");
  std::cout << *s2 << " " << *s3 << " " << *s4 << std::endl;
}
