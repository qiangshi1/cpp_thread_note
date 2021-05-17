// std::recursive_mutex和std::mutex的效率比较
// 结论: 效率好像搞不了多少, 老师讲的存疑

#include <iostream>
#include <thread>
#include <list>
#include <mutex>

class AC
{
public:
    std::list<int> ints;
#define CONDITION 0
#if CONDITION == 0
// 用独占锁, 测试程序执行时间结果为:
// real	0m10.268s
// user	0m12.724s
// sys	0m7.573s
    std::mutex m;
#elif CONDITION == 1
// 用递归锁, 测试程序执行时间结果为:
// real	0m10.909s
// user	0m13.356s
// sys	0m8.272s
    std::recursive_mutex m;
#else
#endif

    void setInts()
    {

        for (int i = 0; i < 10000000; i++)
        {
            m.lock();
            ints.push_back(i);
            m.unlock();
        }
    }
    void getInts()
    {

        for (int i = 0; i < 10000000; i++)
        {
            m.lock();
            if (!ints.empty())
            {
                int a_int = ints.front(); //取队首
                ints.pop_front();         //删除队首
            }
            else
            {
            }
            m.unlock();
        }
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