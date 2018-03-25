#include <iostream>
#include <thread>
#include "ThreadPool.hpp"

using namespace std;
using namespace std::chrono_literals;

void printHelloWorld() {
   std::cout << "hello World" << std::endl;
}

int main() {

    {
        ThreadPool t(5, 100);
        t.run();

        for (int i = 0; i < 100; ++i) {
            std::cout << "add " << i << "task ok..." << std::endl;
            t.addTask(printHelloWorld);
        }

        std::this_thread::sleep_for(10s);
        t.stop();
    }
    std::cout << "finished here" << std::endl;
    return 0;
}