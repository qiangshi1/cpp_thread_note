// 虚假唤醒
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>
#include <mutex>
#include <unistd.h>
#include <condition_variable>

class AC
{
public:
    std::list<int> ints;
    std::mutex m;
    std::condition_variable cv;
    void setInts()
    {
        for (int i = 0; i < 100000; i++)
        {
            std::unique_lock<std::mutex> lg(m);
            ints.push_back(i);
            std::cout << "set: " << i << std::endl;
            cv.notify_one();  
        }
    }
    void getInts()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lg(m);
            // 这块代码完全摘自19-10.cc, 这块代码已经把虚假唤醒处理得很好了, 关注if(!ints.empty())这个if判断 
            cv.wait(lg, [this]
                    {
                        if (!ints.empty())
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    });
            int a_int=ints.front(); 
            std::cout<<"get: "<<a_int<<std::endl;
            ints.pop_front(); 

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