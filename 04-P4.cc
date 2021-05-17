// lambda表达式用作线程
#include <iostream>
#include <thread>
// #include <functional>
int main(int argc, char const *argv[])
{
    auto a_lambda_func = []
    {
        std::cout << "a lambda func is running!" << std::endl;
    };
    std::thread trd(a_lambda_func); trd.join();
    return 0;
}