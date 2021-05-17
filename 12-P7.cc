// 线程共享资源问题----加锁(互斥量)保证数据安全
// 测试不会崩溃了
// 用std::lock_guard可以避免忘记写unlock()
// 但是用std::lock_guard没有用lock() unlock()灵活
// 被保护的量不要被函数返回, 否则会穿透锁的保护域
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>

class AC{
    public:
    std::list<int> ints;
    std::mutex m;
    void setInts(){
        
        for(int i=0;i<200000;i++){
            std::cout<<"set: "<<i<<std::endl;
            // lock()和unlock()成对使用
            m.lock();
            ints.push_back(i); //
            m.unlock();
        }
        
    }
    void getInts1(){
        
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
    void getInts2(){
        for(int i=0;i<100000;i++){
            m.lock();
            std::cout<<"second get: "<<i<<std::endl;
            if(!ints.empty()){
                int a_int=ints.front(); //取队首
                ints.pop_front(); //删除队首
            }else{
                std::cout<<"second ints is empty! i is: "<<i<<std::endl;
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
    std::thread trd_getter1(&AC::getInts1, &ac);
    std::thread trd_getter2(&AC::getInts2, &ac);
    trd_setter.join();
    trd_getter1.join();
    trd_getter2.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}