// 线程共享资源问题----为什么我的不崩溃?
// 老师的例子似乎不会崩溃, 一个读一个写, 再加上读的还有空判定, 所以不会崩溃, 我改成可一个写, 两个读. 测试成功出现崩溃
// 也可能是我没有跟对老师的代码
// 这个错误是代码级的, 还会出现汇编级的代码
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <list>

class AC{
    public:
    std::list<int> ints;
    void setInts(){
        for(int i=0;i<200000;i++){
            std::cout<<"set: "<<i<<std::endl;
            ints.push_back(i); //
        }
    }
    void getInts1(){
        for(int i=0;i<100000;i++){
            std::cout<<"first get: "<<i<<std::endl;
            if(!ints.empty()){
                int a_int=ints.front(); //取队首
                ints.pop_front(); //删除队首
            }else{
                std::cout<<"first ints is empty! i is: "<<i<<std::endl;
            }
        }
        std::cout<<"getInts finished."<<std::endl;
    }
    void getInts2(){
        for(int i=0;i<100000;i++){
            std::cout<<"second get: "<<i<<std::endl;
            if(!ints.empty()){
                int a_int=ints.front(); //取队首
                ints.pop_front(); //删除队首
            }else{
                std::cout<<"second ints is empty! i is: "<<i<<std::endl;
            }
        }
        std::cout<<"getInts finished."<<std::endl;
    }
};

int main(int argc, char const *argv[])
{
    AC ac;
    std::thread trd_setter(&AC::setInts, &ac);
    std::thread trd_getter1(&AC::getInts1, &ac);
    std::thread trd_getter2(&AC::getInts2, &ac);
    trd_setter.join();
    trd_getter1.join();
    trd_getter2.join();
    std::cout << "this is main!" << std::endl;
    return 0;
}