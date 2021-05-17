// 单例模式----多线程会破坏单例
#include <iostream>
#include <thread>
#include <unistd.h>

class SingletonClass{
    public:
    static SingletonClass* GetInstance(){
        static SingletonClass* instance=nullptr; 
        if(instance==nullptr){
            // sleep(1); //为了让问题更明显, 这边可以加一个sleep函数. 
            instance = new SingletonClass();
        }
        return instance;
    }
    private:
    SingletonClass(){}; 

};
void a_func(){
    SingletonClass* scp=SingletonClass::GetInstance();
    std::cout<<std::endl<<scp<<std::endl; //多线程非常有可能创建两个实例, 这会破坏单例的单例性. 表现为这里打印的两个地址不一样. 
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