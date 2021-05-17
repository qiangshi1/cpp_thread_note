// 类函数用作线程 1
#include <iostream>
#include <thread>
class AC{
public:
    int &m_i;
    AC(int & i): m_i(i){}
    void operator() (){
        std::cout<<"in class thread 1"<<std::endl;
        std::cout<<"m_i: "<<m_i<<std::endl;
    }
};
int main(int argc, char const *argv[])
{
    int myi=6;
    AC ac(myi);
    std::thread trd(ac); 
    trd.detach();// myi是主线程的局部变量, 当主线程执行完毕, myi会回收, 子线程中的m_i就不知道是谁的引用了, 会出现不可预知的错误. 用trd.join();没有这个问题
    
}