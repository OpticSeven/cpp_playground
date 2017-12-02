
#include <type_traits>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <iostream>
#include <utility>

class ThreadPool{
    public:
    static ThreadPool& instance();
    void create_threads(unsigned int threadCount);
    
    template <typename F,typename ...Args, typename T = typename std::result_of<F&(Args...)>::type>
    std::future<T> async(std::promise<T>& promise, F f, Args... arguments);

    private:
    ThreadPool(){};
    //ThreadPool(const ThreadPool& other) = delete;
   // ThreadPool& operator=(const ThreadPool &other) = delete;
    void threadworker();

    template <typename F,typename ...Args, typename T = typename std::result_of<F&(Args...)>::type>
    void wrapped_function(std::promise<T>& promise, F f, Args... arguments);

    std::condition_variable wake_cv;
    std::vector<std::thread> thread_pool;
    std::vector<std::function<void()>> task;
    std::mutex tmutex;

};

#include "async.cpp"