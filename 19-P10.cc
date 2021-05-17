// 条件变量: std::condition_variable wait() notify_one()
// 用std::condition_variable wait() notify_one()会节省效率
// 注意这个演示程序无法退出
// notify_one()可能无法唤醒线程(当线程在执行时)----你永远无法叫醒一个醒着的人. 
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
            cv.notify_one();  //唤醒cv.wait()
            // sleep(1);
        }
    }
    void getInts()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lg(m);
            // 1. wait(锁, 布尔值), 如果布尔值是false, wait()将解锁互斥量, 并堵塞本行, 进入等待唤醒状态; 如果布尔值是true, wait()直接返回. 
            // 2. wait(锁)(和1.相比没有第二个参数),等价于wait(锁, false) 
            // 3. 当其他线程将本wait()唤醒后, wait()会尝试重新上lg锁, 如果无法上锁, 卡在这儿不断地寻求上锁; 如果上锁,  wait()继续执行: ->判断布尔值(其实就是再执行步骤1. ), 如果布尔值为false, wait()将解锁互斥量, 并堵塞本行, 进入等待唤醒状态; 如果布尔值是true, wait()直接返回. 
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
            // 这块是加着锁的
            int a_int=ints.front(); 
            std::cout<<"get: "<<a_int<<std::endl;
            ints.pop_front(); 

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