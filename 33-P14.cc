// 测试try_lock_for()是轮询还是等待----轮询
//
#include <iostream>
#include <thread>
#include <list>
#include <mutex>
#include <unistd.h>

class AC
{
public:
    std::timed_mutex m;
    void setInts()
    {
        sleep(1); //确保线程trd_getter先执行
        auto time_here = std::chrono::steady_clock::now();
        // 到这线程trd_getter拿到锁, 并执行了1s
        if (m.try_lock_for(std::chrono::milliseconds(5000))) //5s
        {
            std::cout << "set: get timed_mutex! " << std::endl;
            m.unlock();
        }
        else
        {
            std::cout << "set: don not get timed_mutex! " << std::endl;
        }
        // 下行测试结果是1s, 说明m.try_lock_for()会轮询尝试拿锁
        std::cout << "time interval: " << std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - time_here).count()<<"s." << std::endl;
    }
    void getInts()
    {
        m.lock();
        sleep(2);
        m.unlock();
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