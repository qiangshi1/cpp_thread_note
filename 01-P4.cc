// join() detach() joinable()
#include <iostream>
#include <thread>

void a_thread_func()
{
    std::cout << "in thread 1" << std::endl;
    std::cout << "in thread 2" << std::endl;
    std::cout << "in thread 3" << std::endl;
    std::cout << "in thread 4" << std::endl;
    std::cout << "in thread 5" << std::endl;
    std::cout << "in thread 6" << std::endl;
    std::cout << "in thread 7" << std::endl;
    std::cout << "in thread 8" << std::endl;
    std::cout << "in thread 9" << std::endl;
    std::cout << "in thread 10" << std::endl;
    std::cout << "in thread 11" << std::endl;
    std::cout << "in thread 12" << std::endl;
    std::cout << "in thread 13" << std::endl;
    std::cout << "in thread 14" << std::endl;
    std::cout << "in thread 15" << std::endl;
    std::cout << "in thread 16" << std::endl;
    std::cout << "in thread 17" << std::endl;
    std::cout << "in thread 18" << std::endl;
    std::cout << "in thread 19" << std::endl;
    std::cout << "in thread 20" << std::endl;
    std::cout << "in thread 21" << std::endl;
    std::cout << "in thread 22" << std::endl;
    std::cout << "in thread 23" << std::endl;
    std::cout << "in thread 24" << std::endl;
    std::cout << "in thread 25" << std::endl;
    std::cout << "in thread 26" << std::endl;
    std::cout << "in thread 27" << std::endl;
    std::cout << "in thread 28" << std::endl;
    std::cout << "in thread 29" << std::endl;
    std::cout << "in thread 30" << std::endl;
}

int main(int argc, char const *argv[])
{
    std::thread trd(a_thread_func);
#define CONDITION 7
#if CONDITION == 0
// 不加join()或者detach()程序执行完毕会报错
#elif CONDITION == 1
    // 加join()表示主线程等待子线程执行完毕再结束
    trd.join();
#elif CONDITION == 2
    // 加detach()表示主线程不等子线程执行完毕就结束, 若子线程未执行完毕会被交给运行时库管理, 有点类似于守护进程
    trd.detach();
#elif CONDITION == 3
    // 先使用detach(), 再使用join()会报错, 因为线程一旦被detach()就不能被join()了.
    trd.detach();
    trd.join();
#elif CONDITION == 4
    // 先使用join(), 再使用detach()也会报错.
    trd.join();
    trd.detach();
#elif CONDITION == 5
    // 用joinable()可以判断线程是否可以被join()
    std::cout << trd.joinable() << std::endl;
#elif CONDITION == 6
    // 用joinable()可以判断线程是否可以被join()
    trd.join();
    std::cout << trd.joinable() << std::endl;
#elif CONDITION == 7
    // 用joinable()可以判断线程是否可以被join()
    trd.detach();
    std::cout << trd.joinable() << std::endl;
#endif
    std::cout << "in main 1" << std::endl;
    std::cout << "in main 2" << std::endl;
    std::cout << "in main 3" << std::endl;
    return 0;
}