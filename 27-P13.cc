// std::atomic 原子操作----原子类型支持的运算
// 原子类型并不支持所有它模板支持的运算. 

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
        //测试原子类型支持的运算
        a_global_int++; //支持
        // a_global_int+=1; //支持
        // a_global_int=a_global_int+1; //不支持, 编译通过, 但运算结果不对
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