// std::packaged_task
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
#define CONDITION 3
#if CONDITION == 0
    std::packaged_task<int(int)> pt(a_func); //相当于用std::package包装了一层a_func, 类似于智能指针和指针的关系
    std::thread trd(std::ref(pt), 10);
    trd.join();                                           //join()不可省略
    std::future<int> result = pt.get_future();            //取线程的返回值
    std::cout << "result: " << result.get() << std::endl; //取线程的返回值
#elif CONDITION == 1
    std::packaged_task<int(int)> pt(a_func);
    std::thread trd(std::ref(pt), 10);
    std::future<int> result = pt.get_future();
    std::cout << "result: " << result.get() << std::endl;
    trd.join(); //join()放在这也可以, 用CONDITION==1和==2体会join()的逻辑
#elif CONDITION == 2
    // std::packaged_task+lambda表达式
    std::packaged_task<int(int)> pt([](int a_int)
                                    {
                                        std::cout << "this is a lambda func!: " << std::this_thread::get_id() << std::endl;
                                        a_int++;
                                        sleep(5);
                                        return a_int;
                                    });
    std::thread trd(std::ref(pt), 10);
    trd.join();                                         
    std::future<int> result = pt.get_future();         
    std::cout << "result: " << result.get() << std::endl; 
#elif CONDITION == 3
    // 也可以这样写, 并没有创建线程
    std::packaged_task<int(int)> pt([](int a_int)
                                    {
                                        std::cout << "this is a lambda func!: " << std::this_thread::get_id() << std::endl;
                                        a_int++;
                                        sleep(5);
                                        return a_int;
                                    });
    pt(10);                                       
    std::future<int> result = pt.get_future();         
    std::cout << "result: " << result.get() << std::endl; 
#else
#endif // CONDITION
    std::cout << "this is main end!:" << std::this_thread::get_id() << std::endl;
    return 0;
}