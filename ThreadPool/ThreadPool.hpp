//
// Created by ender on 3/24/18.
//

/*
 *  注意点:
 *  1. `unique_lock` 和 `lock_guard` 使用是有区别的, 前者更加灵活,可以搭配条件变量而后者不可以.
 *  2. 任务停止的时候保证所有线程资源退出, 这里包括两点: 所有的变量状态; 所有条件变量需要唤醒
 *  3. 同理, 线程开始工作也要考虑上面这两点
 *
 *  对于线程阻塞来说, 可以通过超时kill掉这种机制来保证, 可以参考https://github.com/ender233/myThreadPool
 *
 */
#ifndef THREADTOOL_THREADPOOL_HPP
#define THREADTOOL_THREADPOOL_HPP

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <vector>
#include <boost/enable_shared_from_this.hpp>
using namespace std;

typedef std::function<void()> TaskThread;
typedef std::unique_ptr<std::thread> Thread_ptr;
typedef std::vector<Thread_ptr> VecThread;

class ThreadPool :
        public boost::enable_shared_from_this<ThreadPool>
{

public:
    ThreadPool(int threadNums, int threadPoolSize) :
            willStop_ (false),
            threadNums_(threadNums),
            threadPoolSize_(threadPoolSize)
    {

    }

    virtual ~ThreadPool() {
        stop();
    }

    void stop() {
        willStop_ = true;

        m_notEmpty_.notify_all();
        m_notFull_.notify_all();
    }
    void run() {
        willStop_ = false;

        for(int i=0; i<threadNums_; ++i) {
            Thread_ptr taskPtr = std::make_unique<std::thread>([this](){
                std::cout<<"begin to run the thread id : "<< std::this_thread::get_id() << std::endl;
                this->consumeThread();
            });

            threads_.push_back(std::move(taskPtr));
        }

        m_notFull_.notify_all();
        std::cout << "begin to run the threadPool..." << std::endl;

        for(auto &t : threads_) {
            t->detach();
        }
    }

    void addTask(TaskThread task) {
        // add
        std::unique_lock<std::mutex> locker(mutex_);
        m_notFull_.wait(locker, [this](){
            return willStop_ || (!isFull());
        });

        queue_.push_back(task);

        // notify
        m_notEmpty_.notify_one();
    }

    void consumeThread() {
        while(true) {
            std::unique_lock<std::mutex> locker(mutex_);
            m_notEmpty_.wait(locker, [this](){
                return willStop_ || (!isEmpty());
            });

            if(willStop_) break;

            TaskThread t = queue_.front();
            queue_.pop_front();

            t();

            // notify
            m_notFull_.notify_one();
        }
    }

private:
    bool isFull() {
        //std::lock_guard<std::mutex> locker(mutex_);
        return queue_.size() == threadPoolSize_;
    }

    bool isEmpty() {
        //std::lock_guard<std::mutex> locker(mutex_);
        return queue_.size() == 0;
    }

private:
    std::list<TaskThread>   queue_;
    std::mutex              mutex_;
    bool                    willStop_;
    int                     threadNums_;
    int                     threadPoolSize_;
    VecThread               threads_;

    std::condition_variable m_notEmpty_;
    std::condition_variable m_notFull_;
};

#endif //THREADTOOL_THREADPOOL_HPP
