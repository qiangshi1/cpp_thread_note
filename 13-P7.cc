// 线程共享资源问题----死锁问题
// 死锁问题的产生至少由两个互斥量产生
// 只要保证互斥量上锁的顺序一致, 就不会死锁
// 也可以用std::lock()一次锁住两个或者多个互斥量, 来避免死锁
// 一个扩展 std::adopt_lock
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <unistd.h>

class AC
{
public:
    std::mutex m1;
    std::mutex m2;
    void func1()
    {
        m1.lock();
        sleep(1); //延迟确保死锁产生
        m2.lock();
        std::cout << "func1" << std::endl;
        m2.unlock();
        m1.unlock();
    }
    void func2()
    {
#define CONDITION 1
#if CONDITION == 0 // 有死锁
        m2.lock();
        sleep(1); //延迟确保死锁产生
        m1.lock();
        std::cout << "func2" << std::endl;
        m1.unlock();
        m2.unlock();
#elif CONDITION == 1 // 没有死锁
        m1.lock();
        sleep(1); //延迟确保死锁产生
        m2.lock();
        std::cout << "func2" << std::endl;
        m2.unlock();
        m1.unlock();
#else
#endif
    }
};

int main(int argc, char const *argv[])
{
    AC ac;
    std::thread trd1(&AC::func1, &ac);
    std::thread trd2(&AC::func2, &ac);
    trd1.join();
    trd2.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}