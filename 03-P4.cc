// 类函数用作线程 2
#include <iostream>
#include <thread>
class AC{
public:
    int m_i;
    AC(int i): m_i(i){
        std::cout<<"create AC"<<std::endl;
    }
    AC(const AC& ac): m_i(ac.m_i){
        std::cout<<"copy AC"<<std::endl;
    }
    ~AC(){
        std::cout<<"destory AC"<<std::endl;
    }
    void operator() (){
        std::cout<<"in class thread 1"<<std::endl;
    }
};
int main(int argc, char const *argv[])
{
    int myi=6;
    AC ac(myi);
    std::thread trd(ac); //ac是被复制到了线程中去了. 可以看到析构函数被执行了2次, 不过为什么我的有时候会被执行3次呢? 又是还会执行4次?
    // 和我遇到相同问题的一个帖子: https://segmentfault.com/q/1010000018068102 他说是编译器的问题, 他并没有解释析构函数有时会被执行3-4次, 而且他也讲得也不是很明白
    trd.detach();
    return 0;
}