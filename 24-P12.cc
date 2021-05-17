// std::future的其他用法: wait_for() std::future_status::timeout std::future_status::ready std::future_status::deferred
#include <iostream>
#include <unistd.h> // sleep
#include <future>   // std::future

int a_func1()
{
    std::cout << "this is a func!: " << std::this_thread::get_id() << std::endl;
    sleep(5);
    return 5;
}

int main(int argc, char const *argv[])
{
    std::cout << "this is main start!: " << std::this_thread::get_id() << std::endl;
    std::future<int> result=std::async(std::launch::async, a_func1);  //async()的默认参数好像不一定是std::launch::async, 似乎是编译器选择的, 我这里写上std::launch::async才和老师演示的一样. 
    std::future_status status=result.wait_for(std::chrono::seconds(1)); //主线程等待1s
    if(status==std::future_status::timeout){ 
        // 超时, 表示线程还没有执行完, 这一行会执行, 因为线程要5s, 程序到这里要1s
        std::cout<<"1. thread is not end! "<< std::endl;
    }
    status=result.wait_for(std::chrono::seconds(5));  //主线程再等待5s
    if(status==std::future_status::timeout){ 
        // 这一行不会执行
        std::cout<<"2. thread is not end! "<< std::endl;
    }else if(status==std::future_status::ready){
        // 线程执行完毕, 这一行会执行
        std::cout<<"2. thread has been returned! "<< std::endl;
    }
    // 还有std::future_status::deferred, 它是针对std::async(std::launch::deferred, a_func1)的, 我不在演示了. 
    std::cout << "this is main end!: " << std::this_thread::get_id() << std::endl;
    return 0;
}