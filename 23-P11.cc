// std::promise, 它是用于线程之间的值传递
#include <iostream>
#include <unistd.h> // sleep
#include <future>   // std::promise std::future

void a_func1(std::promise<int>& res, int a_int)
{
    std::cout << "this is a func!: " << std::this_thread::get_id() << std::endl;
    sleep(5);
    res.set_value(a_int*a_int);
    return;
}

int main(int argc, char const *argv[])
{
    std::cout << "this is main start!: " << std::this_thread::get_id() << std::endl;
    std::promise<int> pm; 
    std::thread trd1(a_func1, std::ref(pm), 10);
    trd1.join();
    std::future<int> result=pm.get_future(); //获取pm的值, 100=10*10
    std::cout << "result: " << result.get() << std::endl; //获取pm的值, 100=10*10
    std::cout << "this is main end!:" << std::this_thread::get_id() << std::endl;
    return 0;
}