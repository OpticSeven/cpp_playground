#include <thread>
#include <type_traits>
#include "async.h"

    
asn::ThreadPool::ThreadPool& instance(){
{
   // The only instance
   // Guaranteed to be lazy initialized
   // Guaranteed that it will be destroyed correctly
   static ThreadPool instance;
   return instance;
 }
