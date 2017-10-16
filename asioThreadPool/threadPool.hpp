#pragma once
#include <iostream> 
#include <thread>
#include <vector>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;
typedef std::shared_ptr<std::thread> thread_ptr;
typedef std::vector<thread_ptr> vecThread;

class ThreadPool {
public:
    ThreadPool(int num) : threadNum_(num), stopped_(false), work_(io_) {
        for(int i=i; i<threadNum_; ++i) {
            threads_.push_back(std::make_shared<std::thread>([&](){io_.run();}));
        }
    }
    ~ThreadPool() {
        stop();  
    }
    template<typename F, typename...Args>
    void post(F &&f, Args&&...args) {
        io_.post(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    }
    void stop() {
        if(!stopped_) {
            io_.stop();       
            for(auto t : threads_) t->join();
            stopped_ = true;
        }
    }

private:
    bool             stopped_;
    vecThread        threads_;
    int              threadNum_;
    asio::io_service io_;
    asio::io_service::work work_;
};
