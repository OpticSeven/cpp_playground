
#ifndef _ASYNC_H
#define _ASYNC_H
#include <type_traits>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>

class ThreadPool{
    public:
    static ThreadPool& instance(unsigned int threadCount);
    
    template <typename F,typename ...Args, typename T = typename std::result_of<F&(Args...)>::type>
    std::future<T> async(std::promise<T>& promise, F f, Args... arguments);

    private:
    ThreadPool(){};
    void create_threads(unsigned int threadCount);
    ThreadPool(const ThreadPool& other) = delete;
    ThreadPool& operator=(const ThreadPool &other) = delete;
    void threadworker();

    std::condition_variable wake_cv;
    std::vector<std::thread> thread_pool;
    std::queue<std::function<void()>> task;
    std::mutex tmutex;
    bool thread_created = false;

};

//template definitions

template <typename F,typename ...Args, typename T>
std::future<T> ThreadPool::async(std::promise<T>& promise, F f, Args... arguments)  {
promise;
    {
      std::lock_guard<std::mutex> lck(tmutex);
      task.push([=, &promise]() mutable{
        promise.set_value(f(arguments...));
      });
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    wake_cv.notify_one();

    return  std::move(promise.get_future());
    
};

#endif