// join()主线程等待子线程返回后在往下执行
#include <iostream>
#include <thread>
#include <unistd.h>

class AC{
    public:
    void func1(){
        sleep(5);
    }
    void func2(){
        sleep(5);
    }
    void func3(){
        sleep(5);
    }
};

int main(int argc, char const *argv[])
{
    AC ac;
    std::cout << "this is main 1!" << std::endl;
    std::thread trd1(&AC::func1, &ac);
    trd1.join();
    std::cout << "this is main 2!" << std::endl;
    std::thread trd2(&AC::func2, &ac);
    trd2.join();
    std::cout << "this is main 3!" << std::endl;
    std::thread trd3(&AC::func3, &ac);
    trd3.join();
    std::cout << "this is main 4!" << std::endl;
    return 0;
}