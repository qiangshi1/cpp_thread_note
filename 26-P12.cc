// std::atomic 原子操作----汇编级的多线程特性会导致a_glabal_int达不到20000000. 网上有很多用cpu-寄存器-内存的读写模型解释该现象的帖子
// 当然用互斥锁可以解决这个现象
#include <iostream>
#include <unistd.h> // sleep
#include <thread>
#include <mutex>
#include <atomic>

#define CONDITION 2
#if CONDITION == 0
// 1. 加不到20000000
int a_global_int = 0;
void a_func()
{
    for (int i = 0; i < 10000000; i++)
    {
        a_global_int++;
    }
    return;
}
#elif CONDITION == 1
// 2. 用互斥锁可以解决1.中的问题
// 若用time ./a.out测试程序运行时间, 结果为:
// real    0m1.655s
// user    0m2.263s
// sys     0m0.996s
int a_global_int = 0;
std::mutex m;
void a_func()
{
    for (int i = 0; i < 10000000; i++)
    {
        m.lock();
        a_global_int++;
        m.unlock();
    }
    return;
}
#elif CONDITION == 2
// 2. 原子操作也可以解决1.中的问题
// 原子约等于无锁, 原子是多线程中不能被打断的程序片段
// 若用time ./a.out测试程序运行时间, 结果为:
// real    0m0.406s
// user    0m0.765s
// sys     0m0.000s
// 可见原子操作比互斥量更具效率(有说针对基础类型才更具效率的, 意思是对于复杂类/结构体原子操作的效率可能比互斥量低, 有机会再测试)

// std::atomic<int> a_global_int = 0;
std::atomic<int> a_global_int(0); //上面的初始化方法编译不通过, 要用这一行
void a_func()
{
    for (int i = 0; i < 10000000; i++)
    {
        a_global_int++;
    }
    return;
}
#else
#endif

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