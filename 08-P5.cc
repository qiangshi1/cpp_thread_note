// 成员函数作为线程的入口函数
#include <iostream>
#include <thread>
#include <string>

class AC
{
public:
    int m_i;
    AC(int i) : m_i(i)
    {
        std::cout << "create AC: thread id: " << std::this_thread::get_id() << std::endl;
    }
    AC(const AC &ac) : m_i(ac.m_i)
    {
        std::cout << "copy AC: thread id: " << std::this_thread::get_id() << std::endl;
    }
    void a_func(const int& num)
    {
        std::cout << "a_func: thread id: " << std::this_thread::get_id() << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    std::cout << "main: thread id: " << std::this_thread::get_id() << std::endl;
    AC ac(100);
#define CONDITION 1
#if CONDITION == 0
    std::thread trd(&AC::a_func, ac, 15);
#elif CONDITION == 1
    // 所以这里类ac既可以写值也可以写地址? 同时减少拷贝构造函数
    std::thread trd(&AC::a_func, &ac, 15);
#elif CONDITION == 2
#else
#endif
    trd.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}