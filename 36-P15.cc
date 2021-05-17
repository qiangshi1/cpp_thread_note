// std::atomic----续27-p13.cc
#include <iostream>
#include <unistd.h> // sleep
#include <thread>
#include <mutex>
#include <atomic>

std::atomic<int> a_global_int(0); 
void a_func()
{
    for (int i = 0; i < 10000000; i++)
    {
        // a_global_int++; //支持
        // auto a_int=a_global_int; // 不支持, 编译器报错 
        auto a_int(a_global_int.load()); // 这种写法是支持的
        a_global_int.store(12); // 这种写法是支持的
    }
    return;
}

int main(int argc, char const *argv[])
{
    std::cout << "this is main start!: " << std::this_thread::get_id() << std::endl;
    std::thread trd1(a_func);
    std::thread trd2(a_func);
    trd1.join();
    trd2.join();
    std::cout << "a_global_int: " << a_global_int << std::endl;
    std::cout << "this is main end!:" << std::this_thread::get_id() << std::endl;
    return 0;
}