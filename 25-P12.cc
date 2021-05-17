// std::shared_future, 普通future在线程返回结果后只能用一次get()得到该结果, 而std::shared_future可以用多次get()
#include <iostream>
#include <unistd.h> // sleep
#include <future>   // std::packaged_task.

int a_func(int a_int)
{
    std::cout << "this is a func!: " << std::this_thread::get_id() << std::endl;
    a_int++;
    sleep(5);
    return a_int;
}

int main(int argc, char const *argv[])
{
    std::cout << "this is main start!: " << std::this_thread::get_id() << std::endl;
    std::packaged_task<int(int)> pt(a_func);
    std::thread trd(std::ref(pt), 10);
#define CONDITION 1
#if CONDITION == 0
    // 编译会通过, 运行会报错
    std::future<int> result = pt.get_future();
    std::cout << "future 1. result: " << result.get() << std::endl;
    std::cout << "future 2. result: " << result.get() << std::endl;
#elif CONDITION == 1
    // 运行通过
    std::shared_future<int> result = pt.get_future();
    std::cout << "future 1. result: " << result.get() << std::endl;
    std::cout << "future 2. result: " << result.get() << std::endl;
    std::cout << result.valid()<< std::endl; //result.valid()判断result是否有值, 即能否调用result.get(), 这里输出 1 .
#else
#endif
    trd.join();
    std::cout << "this is main end!:" << std::this_thread::get_id() << std::endl;
    return 0;
}