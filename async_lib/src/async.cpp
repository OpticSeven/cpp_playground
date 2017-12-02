
/*
 ThreadPool::ThreadPool({
   if (threadCount > std::thread::hardware_concurrency()){
      std::cout << "warning thread count exceeds hardware maximum of " << std::thread::hardware_concurrency() << std::endl;
   }
   for (size_t n=0; n<threadCount; ++n){
     thread_pool.push_back(std::thread(&ThreadPool::threadworker,this));
   }
 };
*/

 void ThreadPool::create_threads(unsigned int threadCount){
   if (threadCount > std::thread::hardware_concurrency()){
      std::cout << "warning thread count exceeds hardware maximum of " << std::thread::hardware_concurrency() << std::endl;
   }
   for (size_t n=0; n<threadCount; ++n){
     thread_pool.push_back(std::thread(&ThreadPool::threadworker,this));
   }
 };

 ThreadPool& ThreadPool::instance(){
   // The only instance
   // Guaranteed to be lazy initialized
   // Guaranteed that it will be destroyed correctly
   static ThreadPool instance;
   return instance;
 };

void ThreadPool::threadworker(){
  std::unique_lock<std::mutex> lck(tmutex);
  std::cout<<"thread launched"<<std::endl;
  while (1){
    wake_cv.wait(lck);

    if(!task.empty()){
      task[0](); //run task TODO: CHANGE TO STACK FOR DELETES
    }
  }
};

template <typename F,typename ...Args, typename T>
std::future<T> ThreadPool::async(std::promise<T>& promise, F f, Args... arguments)  {
promise;
    {
      std::lock_guard<std::mutex> lck(tmutex);
      task.push_back([=, &promise]() mutable{
        promise.set_value(f(arguments...));
      });

      
      /*
      task.push_back(std::bind(&ThreadPool::wrapped_function//erererer//,this,promise,f,arguments...));
    */
    }
    wake_cv.notify_one();
    //next
    return  std::move(promise.get_future());
    
};
template <typename F,typename ...Args, typename T >
void ThreadPool::wrapped_function(std::promise<T>& promise, F f, Args... arguments){
    promise.set_value(f(arguments...));
//complete

};

