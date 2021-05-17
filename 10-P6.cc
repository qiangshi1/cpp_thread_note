// 线程共享资源问题----只读数据是安全的
#include <iostream>
#include <thread>
#include <string>
#include <vector>

std::vector<int> ints={1,2,3};
void a_func()
{
    std::cout << "a_func: thread id: " << std::this_thread::get_id() << std::endl;
    #define CONDITION 0
    #if CONDITION==0
    // 1. 只读数据是安全的
    std::cout << "ints: " << ints[0]<<", "<< ints[1]<<", "<< ints[2]<<", " << std::endl;
    #elif CONDITION==1
    #else
    #endif
}

int main(int argc, char const *argv[])
{
    std::cout << "main: thread id: " << std::this_thread::get_id() << std::endl;
    std::vector<std::thread> trds;
    for(int i = 0; i < 10; i++){
        trds.push_back(std::thread(a_func));
    }
    for(auto iter = trds.begin(); iter != trds.end();iter++){
        iter->join();
    }
    std::cout << "this is main!" << std::endl;
    return 0;
}