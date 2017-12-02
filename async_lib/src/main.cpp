#include <iostream>
#include "async.h"

int fun(int x, int y, int z){
   return x+y+z;
};


int main(){
   


   ThreadPool& tp= ThreadPool::instance();
   tp.create_threads(2);
   std::promise<int> answer;
   std::future<int> test = tp.async(answer,fun,1,1,1);
   //asn::future<int> fut = asn::async(fun,1,2,3);
   std::cout << test.get() << std::endl;	
   return 0;
};
//Empty at the moment 
