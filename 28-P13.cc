// std::async续谈
// 如果同时用 std::launch::async | std::launch::deferred 则意味着async的行为可能是 std::launch::async 创建新线程立即执行, 也可能是 std::launch::deferred 没有创建新线程并且延迟到调用get()执行,由系统根据实际情况来决定采取哪种方案. 
// 不带额外参数 std::async(mythread),只给async 一个入口函数名, 此时的系统给的默认值是 std::launch::async | std::launch::deferred 和上一样, 由系统自行决定.

// std::async和std::thread()区别:
// std::thread()面临着系统资源紧张可能出现创建线程失败的情况,如果创建线程失败那么程序就可能崩溃,而且不容易拿到函数返回值(不是拿不到)
// std::async()创建异步任务.可能创建线程也可能不创建线程,并且容易拿到线程入口函数的返回值

// 由于系统资源限制:
// 如果用std::thread创建的线程太多,则可能创建失败,系统报告异常,崩溃.
// 如果用std::async,一般就不会报异常,因为如果系统资源紧张,无法创建新线程的时候,async不加额外参数的调用方式就不会创建新线程.而是在后续调用get()请求结果时执行在这个调用get()的线程上.

// 如果你强制async一定要创建新线程就要使用 std::launch::async 标记.承受的代价是,系统资源紧张时可能崩溃.
// 根据经验,一个程序中线程数量 不宜超过100~200.
// 参考 https://blog.csdn.net/qq_38231713/article/details/106093332


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
    std::future<int> result=std::async(std::launch::async, a_func1);
    // std::future<int> result=std::async(std::launch::async | std::launch::deferred, a_func1); 这种写法貌似不确定是std::launch::async和std::launch::deferred
    std::cout<<"result: "<<result.get()<<std::endl;
    std::cout << "this is main end!: " << std::this_thread::get_id() << std::endl;
    return 0;
}