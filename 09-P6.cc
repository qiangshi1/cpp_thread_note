// 创建和等待多个线程
#include <iostream>
#include <thread>
#include <string>
#include <vector>

void a_func(const int& num)
{
    std::cout << "a_func: thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "num: " << num << std::endl;
}

int main(int argc, char const *argv[])
{
    std::cout << "main: thread id: " << std::this_thread::get_id() << std::endl;
    std::vector<std::thread> trds;
    for(int i = 0; i < 10; i++){
        // 1. 执行顺序: 多个线程的执行顺序是乱的, 和操作系统对线程的调度机制相关
        trds.push_back(std::thread(a_func, i));
    }
    for(auto iter = trds.begin(); iter != trds.end();iter++){
        iter->join();
    }
    std::cout << "this is main!" << std::endl;
    return 0;
}