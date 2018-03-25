#include <iostream>
#include <functional>
#include <list>
#include <thread>
#include <vector>
#include <memory>
#include <chrono>
#include <boost/enable_shared_from_this.hpp>

using namespace std;
using namespace std::chrono_literals;
typedef std::function<void(void)> Func;

typedef std::unique_ptr<std::thread> Threadptr;
typedef std::vector<Threadptr>       ThreadVec;

std::list<Func> list_;

void printHelloWorld()
{
    std::cout << "hello world" << std::endl;
}

void addTask(Func f) {
    list_.push_back(f);
}

class ThreadTest : public enable_shared_from_this<ThreadTest>
{
public:
    void testThread() {
        std::cout << "hello test" << std::endl;
    }

    void runThread() {
        for(int i=0; i<5; ++i) {
            Threadptr t = std::make_unique<std::thread>([this](){
                this->testThread();
            });

            threads_.push_back(std::move(t));
        }

        for(auto &t : threads_) {
            t->detach();
        }
        std::cout << "finished init thread work" << std::endl;
    }

private:
    ThreadVec threads_;
};

int main() {
    /*
    Func t = printHelloWorld;
    t();
    Func t1 = [](){std::cout<<"hello";};
    t1();
     */
    /*
    addTask(printHelloWorld);
    for(auto t : list_) {
        t();
    }

    //
    ThreadVec threads;
    Threadptr t2 = std::make_unique<std::thread>([](){
        printHelloWorld();
    });

    threads.push_back(std::move(t2));

    for(auto &t : threads) {
        t->detach();
    }
     */

    /***************/
    ThreadTest threadTest;
    threadTest.runThread();

    std::this_thread::sleep_for(5s);
}