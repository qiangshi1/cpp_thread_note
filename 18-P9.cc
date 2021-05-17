// 单例模式----std::call_once(c11引入)
#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex> //mutex, once_flag

std::mutex m;
std::once_flag of;
class SingletonClass
{
public:
    static SingletonClass *GetInstance()
    {
        static SingletonClass *instance=nullptr; //C++会保证static多线程安全吗? 
        // call_once可以确保函数(第二个参数)只执行一次, call_once()自带互斥能力, 它是线程安全的, 第一个参数(of(once_flag))有互斥锁的作用. 
        std::call_once(of, [&](){instance = new SingletonClass();});
        return instance;
    }
private:
    SingletonClass(){};
};
void a_func()
{
    SingletonClass *scp = SingletonClass::GetInstance();
    std::cout << std::endl
              << scp << std::endl;
}
int main(int argc, char const *argv[])
{
    std::thread trd1(a_func);
    std::thread trd2(a_func);
    trd1.join();
    trd2.join();
    std::cout << "this is a main!" << std::endl;
    return 0;
}