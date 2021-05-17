// std::timed_mutex std::timed_recursive_mutex
// try_lock_for() 
// 互斥量的超时功能
#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <unistd.h>

class AC
{
public:
    std::list<int> ints;
    std::timed_mutex m;
    // std::mutex m;
    void setInts()
    {

        for (int i = 0; i < 100000; i++)
        {
            // m.try_lock_for()表示等待一段时间尝试获取锁, 所以是这段时间内它会轮询检查锁的状态还是等过了这段时间再检查锁的状态? ----33-P4.cc的测试结果说明是轮询
            if (m.try_lock_for(std::chrono::milliseconds(1000))) //1s
            { 
                std::cout << "set: get timed_mutex! " << std::endl;
                ints.push_back(i);
                m.unlock();
            }else{
                std::cout << "set: don not get timed_mutex! " << std::endl;
                sleep(1);
            }
        }
    }
    void getInts()
    {

        for (int i = 0; i < 100000; i++)
        {
            m.lock();
            if (!ints.empty())
            {
                sleep(2); // 这边加一个延迟函数更容易测出m.try_lock_for()拿不到锁的情况
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            m.unlock();
        }
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