#include <iostream>
#include "async.h"

int fun(int x, int y, int z){
   return x+y+z;
};


int main(){
   
   asn::future<int> fut = asn::async(fun,1,2,3);
   std::cout << fut.value << std::endl;	
   return 0;
};
//Empty at the moment 
