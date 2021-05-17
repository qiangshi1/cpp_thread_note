// std::timed_mutex std::timed_recursive_mutex
// try_lock_until()
// std::timed_recursive_mutex和std::timed_mutex类似, 相当于在std::timed_mutex基础上加上了一个递归功能, 不再演示std::timed_mutex
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
    void setInts()
    {

        for (int i = 0; i < 100000; i++)
        {
            // try_lock_until()和try_lock_for()的功能极其类似, 不过try_lock_until()用的是绝对时间, try_lock_for()用的是相对时间
            // 所以要加std::chrono::steady_clock::now()
            if (m.try_lock_until(std::chrono::steady_clock::now()+std::chrono::milliseconds(1000))) //1s
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
                sleep(2); // 
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