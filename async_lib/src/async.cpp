#include "async.h"

 void ThreadPool::create_threads(unsigned int threadCount){
   if (thread_created == true){
     return;
   }
   thread_created = true;
   if (threadCount > std::thread::hardware_concurrency()){
      std::cout << "warning thread count exceeds hardware maximum of " << std::thread::hardware_concurrency() << std::endl;
   }
   for (size_t n=0; n<threadCount; ++n){
     thread_pool.push_back(std::thread(&ThreadPool::threadworker,this));
   }
 };
 

 ThreadPool& ThreadPool::instance(unsigned int threadCount){
   // The only instance
   // Guaranteed to be lazy initialized
   // Guaranteed that it will be destroyed correctly
   static ThreadPool instance;
   instance.create_threads(threadCount);
   return instance;
 };

void ThreadPool::threadworker(){
  std::unique_lock<std::mutex> lck(tmutex);
  std::cout<<"thread launched"<<std::endl;
  while (1){ //need abort flag for joining thread
    wake_cv.wait(lck);
    if(!task.empty()){
      std::cout<<"go!"<<std::endl;
      auto f = task.front();
      task.pop();
      lck.unlock();
      f();

    }
  }
};
