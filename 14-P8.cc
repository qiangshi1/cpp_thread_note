// unique_lock, 更灵活, 效率更低. 关键词: std::adopt_lock std::try_to_lock owns_lock() lock()  unlock() try_lock() 
// 还是推荐用lock_guard
// 锁住的代码片段多, 称为粒度低, 代码执行效率低
// 锁住的代码片段少, 称为粒度高, 代码执行效率高
// 要在合适的地方加锁
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <unistd.h>

class AC
{
public:
    std::list<int> ints;
    std::mutex m;
    void setInts()
    {
        for (int i = 0; i < 100000; i++)
        {
            std::cout << "set: " << i << std::endl;
            m.lock();
            sleep(1);
            ints.push_back(i); //
            m.unlock();
        }
    }
    void getInts()
    {
        for (int i = 0; i < 100000; i++)
        {
#define CONDITION 2
#if CONDITION == 0
            m.lock();
            std::unique_lock<std::mutex> ul(m, std::adopt_lock);
            //用std::adopt_lock可以不用写unlock()
            // 一个unque_lock只能绑定一个mutex
            std::cout << "second get: " << i << std::endl;
            if (!ints.empty())
            {
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            else
            {
                std::cout << "second ints is empty! i is: " << i << std::endl;
            }
#elif CONDITION == 1
            std::unique_lock<std::mutex> ul(m, std::try_to_lock);
            //用std::try_to_lock尝试加锁, 这样可以使子线程在拿不到锁时先做其他的事情
            if (ul.owns_lock())
            {
                std::cout << "second get: " << i << std::endl;
                if (!ints.empty())
                {
                    int a_int = ints.front(); //取队首
                    ints.pop_front();         //删除队首
                }
                else
                {
                    std::cout << "second ints is empty! i is: " << i << std::endl;
                }
            }
            else
            {
                std::cout << "do not get mutex in getInts()" << std::endl;
            }
#elif CONDITION == 2
            std::unique_lock<std::mutex> ul(m, std::defer_lock);
#define CONDITION2 3
#if CONDITION2 == 0
            ul.lock(); //注意这个lock()不是m的, 不用unlock(),
            std::cout << "second get: " << i << std::endl;
            if (!ints.empty())
            {
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            else
            {
                std::cout << "second ints is empty! i is: " << i << std::endl;
            }
#elif CONDITION2 == 1
            ul.lock();
            std::cout << "second get: " << i << std::endl;
            if (!ints.empty())
            {
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            else
            {
                std::cout << "second ints is empty! i is: " << i << std::endl;
            }
            ul.unlock(); //可以lock() unlock() lock() ... 这样往后写, 只要保证最后一个是lock()即可, 这样的作用是可以暂时让出锁.
            std::cout << "give out mutex in getInts()" << std::endl;
            ul.lock();
#elif CONDITION2 == 2
            if (ul.try_lock())
            { //它的功能和上边的try_to_lock()类似
                std::cout << "second get: " << i << std::endl;
                if (!ints.empty())
                {
                    int a_int = ints.front(); //取队首
                    ints.pop_front();         //删除队首
                }
                else
                {
                    std::cout << "second ints is empty! i is: " << i << std::endl;
                }
            }
            else
            {
                std::cout << "do not get mutex in getInts() 2" << std::endl;
            }
#elif CONDITION2 == 3
            std::mutex *pm=ul.release(); //解除ul和m的关系, 返回一个指向m的指针
            std::cout << "second get: " << i << std::endl;
            if (!ints.empty())
            {
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            else
            {
                std::cout << "second ints is empty! i is: " << i << std::endl;
            }
            pm->unlock(); //这边要手动解锁   
#else
#endif

#else
#endif
        }
        std::cout << "getInts finished." << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    AC ac;
    std::thread trd_setter(&AC::setInts, &ac);
    std::thread trd_getter(&AC::getInts, &ac);
    trd_setter.join();
    trd_getter.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}