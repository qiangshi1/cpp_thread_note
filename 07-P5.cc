// 多线程的智能指针
#include <iostream>
#include <thread>
#include <string>
#include <memory>

void a_func(const std::unique_ptr<int> & i_ptr)
{
    std::cout << "a_func: thread id: " << std::this_thread::get_id() << std::endl;
}
int main(int argc, char const *argv[])
{
    std::unique_ptr<int> _i_ptr(new int(100));
    std::cout << "main: thread id: " << std::this_thread::get_id() << std::endl;
#define CONDITION 1
#if CONDITION == 0
    std::thread trd(a_func, _i_ptr); //不可以这样做, 智能指针禁止拷贝赋值, 当然编译会通不过的
#elif CONDITION == 1
    std::thread trd(a_func, std::move(_i_ptr)); //编译通过
#else
#endif
    trd.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}