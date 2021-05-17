// 单例模式----多线程加锁以保护单例,
#include <iostream>
#include <thread>
#include <unistd.h>
#include <mutex>

std::mutex m;
class SingletonClass
{
public:
    static SingletonClass *GetInstance()
    {
        static SingletonClass *instance = nullptr;
#define CONDITION 1
#if CONDITION == 0
// 简单枷锁, 这种方法效率低
        std::unique_lock<std::mutex> ul(m);
        if (instance == nullptr)
        {
            instance = new SingletonClass();
        }
#elif CONDITION == 1
// 条件判断加锁, 这种效率高
// 它本质上是把一些不需要加锁解锁的情况给过滤掉了
        if (instance == nullptr) //这种写法叫双重检查
        {
            std::unique_lock<std::mutex> ul(m);
            if (instance == nullptr)
            {
                instance = new SingletonClass();
            }
        }
#else
#endif //CONDITION 
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