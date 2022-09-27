#include <deque>
#include <iostream>

class RateLimiter {
public:
  RateLimiter(size_t capacity, int limit): capacity{capacity}, limit{limit} {}
 
  bool addRequest(int timestamp) {
    while (!requests.empty() && timestamp - requests.front() > limit) {
      requests.pop_front();
    }
    if (requests.size() == capacity) {
      return false;
    }
    requests.push_back(timestamp);
    return true;
  }

private:
  size_t capacity;
  int limit;
  std::deque<int> requests;
};

int main() {
  RateLimiter limiter(3, 2);
  std::cout << limiter.addRequest(1) << " " << limiter.addRequest(1) << " " << limiter.addRequest(2) << " " << limiter.addRequest(3) << " " << limiter.addRequest(4) << " " << limiter.addRequest(4) << std::endl;
}
