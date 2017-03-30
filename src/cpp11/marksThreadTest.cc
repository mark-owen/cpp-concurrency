#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

std::mutex mtx;

void say_hello(int i) {
  std::lock_guard<std::mutex> mylock(mtx);
  std::cout << "Hello from a thread " << i << std::endl;
}

int main() {
  std::vector<std::thread> threads;
  for(int i=0; i<10; ++i) {
    threads.push_back(std::thread(say_hello, i));

  }
  for(int i=0; i<10; ++i) {
    threads[i].join();
  }
  return 0;
  
}
