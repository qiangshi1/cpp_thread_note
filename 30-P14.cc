// std::recursive_mutex
// std::mutex 不允许同一个线程对一个互斥量多次上锁, 执行期会有异常
// std::recursive_mutex 允许同一个线程对一个互斥量多次上锁
#include <iostream>
#include <thread>
#include <list>
#include <mutex>

class AC{
    public:
    std::list<int> ints;
    std::recursive_mutex m;
    // std::mutex m;
    void setInts(){
        
        for(int i=0;i<100000;i++){
            std::cout<<"set: "<<i<<std::endl;
            // std::recursive_mutex支持多次加锁
            // 据说递归的次数过多会有问题----未测试
            m.lock();
            m.lock();
            ints.push_back(i); 
            m.unlock();
            m.unlock();
        }
        
    }
    void getInts(){
        
        for(int i=0;i<100000;i++){
            m.lock();
            std::cout<<"first get: "<<i<<std::endl;
            if(!ints.empty()){
                int a_int=ints.front(); //取队首
                ints.pop_front(); //删除队首
            }else{
                std::cout<<"first ints is empty! i is: "<<i<<std::endl;
            }
            m.unlock();
        }
        std::cout<<"getInts finished."<<std::endl;
    }
};

int main(int argc, char const *argv[])
{
    AC ac;
    std::thread trd_setter(&AC::setInts, &ac);
    std::thread trd_getter(&AC::getInts, &ac);
    trd_setter.join();
    trd_getter.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}