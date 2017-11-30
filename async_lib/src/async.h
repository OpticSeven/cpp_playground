#include <thread>
#include <type_traits>

namespace asn {
    
    class ThreadPool{
      public:
      static ThreadPool& instance();
          
      private:
      ThreadPool();
      ThreadPool(const ThreadPool& other) = delete;
      ThreadPool& operator=(const ThreadPool &other) = delete;
        
    };
    
    template <typename T> class future{
        public:
        T get(){
            return value;
        }
       // private:
        //future(T value) : value(value) {};
        T value;
    } ;
    
    template <typename F,typename ...Args>
    auto async(F f, Args... arguments) 
    ->asn::future<typename std::result_of<F&(Args...)>::type> {
        asn::future<typename std::result_of< decltype(f)&(Args...)>::type> fut;
        fut.value = f(arguments...);
        return fut;
        
    }
    
    
}
