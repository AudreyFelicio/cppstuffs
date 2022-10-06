#include <iostream>
#include <cassert>

template <typename T>
class CustomUniquePtr {
public:
  CustomUniquePtr(): resource{nullptr} {
#if DEBUG
    std::cout << "T null constructor called" << std::endl;
#endif
  }

  CustomUniquePtr(T* resource): resource{resource} {
#if DEBUG
    std::cout << "T constructor called" << std::endl;
#endif
  }

  CustomUniquePtr(const CustomUniquePtr& other) = delete;

  CustomUniquePtr& operator=(const CustomUniquePtr& other) = delete;

  CustomUniquePtr(CustomUniquePtr&& other) {
#if DEBUG
    std::cout << "T move constructor called" << std::endl;
#endif
    resource = other.resource;
    other.resource = nullptr;
  }

  CustomUniquePtr& operator=(CustomUniquePtr&& other) {
#if DEBUG
    std::cout << "T move assignment called" << std::endl;
#endif
    resource = other.resource;
    other.resource = nullptr;
  }

  T& operator*() {
#if DEBUG
    std::cout << "T* called" << std::endl;
#endif
    return *resource;
  }

  const T& operator*() const {
#if DEBUG
    std::cout << "const T* called" << std::endl;
#endif
    return *resource;
  }

  T* operator->() {
#if DEBUG
    std::cout << "T-> called" << std::endl;
#endif
    return resource;
  }

  const T* operator->() const {
#if DEBUG
    std::cout << "const T-> called" << std::endl;
#endif
    return resource;
  }



  ~CustomUniquePtr() {
#if DEBUG
    std::cout << "T destructor called" << std::endl;
#endif
    delete resource;
  }

private:
  T* resource;
};

template <typename T>
class CustomUniquePtr<T[]> {
public:
  CustomUniquePtr(): resource{nullptr} {
#if DEBUG
    std::cout << "T[] null constructor called" << std::endl;
#endif
  }

  CustomUniquePtr(T* resource): resource{resource} {
#if DEBUG
    std::cout << "T[] constructor called" << std::endl;
#endif
  }

  CustomUniquePtr(const CustomUniquePtr& other) = delete;

  CustomUniquePtr& operator=(const CustomUniquePtr& other) = delete;

  CustomUniquePtr(CustomUniquePtr&& other) {
#if DEBUG
    std::cout << "T[] move constructor called" << std::endl;
#endif
    resource = other.resource;
    other.resource = nullptr;
  }

  CustomUniquePtr& operator=(CustomUniquePtr&& other) {
#if DEBUG
    std::cout << "T[] move assignment called" << std::endl;
#endif
    resource = other.resource;
    other.resource = nullptr;
  }

  T& operator*() {
#if DEBUG
    std::cout << "T[]* called" << std::endl;
#endif
    return *resource;
  }

  const T& operator*() const {
#if DEBUG
    std::cout << "const T[]* called" << std::endl;
#endif
    return *resource;
  }

  T* operator->() {
#if DEBUG
    std::cout << "T[]-> called" << std::endl;
#endif
    return resource;
  }

  const T* operator->() const {
#if DEBUG
    std::cout << "const T[]-> called" << std::endl;
#endif
    return resource;
  }

  T& operator[](size_t index) {
    return resource[index];
  }  

  const T& operator[](size_t index) const {
    return resource[index];
  }

  ~CustomUniquePtr() {
#if DEBUG
    std::cout << "T[] destructor called" << std::endl;
#endif
    delete[] resource;
  }

private:
  T* resource;
};

int main() {
  int* new_int = new int(5);
  CustomUniquePtr<int> uptr(new_int);
  CustomUniquePtr<int> uptr2(std::move(uptr)); 
  assert(*uptr2 == 5);
  int* new_arr = new int[5];
  for (int i = 0; i < 5; ++i) {
    new_arr[i] = i;
  }
  CustomUniquePtr<int[]> uptr3(new_arr);
  CustomUniquePtr<int[]> uptr4(std::move(uptr3));
  for (int i = 0; i < 5; ++i) {
    std::cout << uptr4[i] << " ";
  }
  std::cout << std::endl;
}
