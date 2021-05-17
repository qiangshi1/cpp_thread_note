// 测试参数隐式转换和显式转换分别在主线程中还是在子线程中.
// 主要测试工具: std::this_thread::get_id()
#include <iostream>
#include <thread>
#include <string>

class AC
{
public:
    int m_i;
    AC(int i) : m_i(i)
    {
        std::cout << "create AC: thread id: " << std::this_thread::get_id() << std::endl;
    }
    AC(const AC &ac) : m_i(ac.m_i)
    {
        std::cout << "copy AC: thread id: " << std::this_thread::get_id() << std::endl;
    }
};
void a_func(const AC &ac)
{
    std::cout << "a_func: thread id: " << std::this_thread::get_id() << std::endl;
}
int main(int argc, char const *argv[])
{
    int a_int = 1;
    std::cout << "main: thread id: " << std::this_thread::get_id() << std::endl;
#define CONDITION 3
#if CONDITION == 0
    // 隐转换的话create AC是在子线程中执行的, 不执行copy AC
    std::thread trd(a_func, a_int);
#elif CONDITION == 1
    // 显示转换的话create AC和copy AC都是在主线程中执行的
    std::thread trd(a_func, AC(a_int));
#elif CONDITION == 2
    // 显示转换相当于如下, 还是有经典问题: copy AC执行了两次
    AC ac_temp=AC(a_int);
    std::thread trd(a_func, ac_temp);
#elif CONDITION == 3
    AC ac_temp=AC(a_int);
    //用std::ref包裹对象能减少二次拷贝,虽然不知道为什么, 这或许和右值有关系, 再学习吧~  
    std::thread trd(a_func, std::ref(ac_temp));
#else
#endif
    trd.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}