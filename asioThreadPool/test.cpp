#include <iostream>
#include <thread>
#include "threadPool.hpp"

void test1(int x) {std::cout<<"test 1:"<<x<<std::endl;}
void test2(int y) {std::cout<<"test 2:"<<y<<std::endl;}

int main()
{
    ThreadPool threads(5);
    threads.post([](){std::cout<<"test 1"<<std::endl;});
    threads.post([](){std::cout<<"test 2"<<std::endl;});
    threads.post(test1, 3);
    threads.post(test2, 5);

    std::this_thread::sleep_for(2s);
    threads.stop();
}
