
#include "async.h"
#include <iostream>
#include <future>
#include <chrono>
#include <thread>
int fun(int x, int y, int z){
   std::this_thread::sleep_for(std::chrono::milliseconds(5000));
   return x+y+z;
};


int main(){
   

   ThreadPool& tp= ThreadPool::instance(4);
   //tp.create_threads(2);
   std::promise<int> answer;
   std::promise<int> answer2;
   std::future<int> test = tp.async(answer,fun,1,1,1);
   std::future<int> test2 = tp.async(answer2,fun,1,2,1);
   //asn::future<int> fut = asn::async(fun,1,2,3);
   std::cout << test.get() << std::endl;
   std::cout << test2.get() << std::endl;		
   return 0;
};
//Empty at the moment 
