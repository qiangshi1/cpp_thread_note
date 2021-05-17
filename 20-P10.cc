// 条件变量: notify_all()
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <unistd.h>
#include <condition_variable>

class AC
{
public:
    std::list<int> ints;
    std::mutex m;
    std::condition_variable cv;
    void setInts()
    {
        for (int i = 0; i < 100000; i++)
        {
            std::unique_lock<std::mutex> lg(m);
            ints.push_back(i);
            std::cout << "set: " << i << std::endl;
            // std::cout << "setInts: thread id: " << std::this_thread::get_id() << std::endl;
#define CONDITION 1
#if CONDITION == 0
            cv.notify_one(); //notify_one()一次只能唤醒一个线程, 至于唤醒哪个线程不一定.
            // 所以在屏幕打印中get1: 和get2: 不可能相连
#elif CONDITION == 1
            cv.notify_all(); //notify_all()唤醒所有线程
            // 在屏幕打印中get1: 和get2: 可能相连
#else
#endif // CONDITION
        }
    }
    void getInts1()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lg(m);
            cv.wait(lg, [this]
                    {
                        if (!ints.empty())
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    });
            int a_int = ints.front();
            std::cout << "get1: " << a_int << std::endl;
            // std::cout << "getInts1: thread id: " << std::this_thread::get_id() << std::endl;
            ints.pop_front();
        }
    }
    void getInts2()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lg(m);
            cv.wait(lg, [this]
                    {
                        if (!ints.empty())
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    });
            int a_int = ints.front();
            std::cout << "get2: " << a_int << std::endl;
            // std::cout << "getInts2: thread id: " << std::this_thread::get_id() << std::endl;
            ints.pop_front();
        }
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