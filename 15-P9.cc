// 设计模式----单例模式
#include <iostream>
// 普通类
class NormalClass{
    public:
    ~NormalClass(){
        std::cout<<"NormalClass deleted"<<std::endl;
    };
};
// 单例类
class SingletonClass{
    public:
    static SingletonClass* GetInstance(){
        static SingletonClass* instance=nullptr; // 所以老师的释放方法也没演示, 不过这种方法是自动释放的吧? 释放内存不是执行析构函数吗? 
        if(instance==nullptr){
            instance = new SingletonClass();
        }
        return instance;
    }
    ~SingletonClass(){
        std::cout<<"Singleton deleted"<<std::endl;
    };
    private:
    SingletonClass(){}; // 构造函数私有化

};
// 我的和老师不一样, 这里会报错, 所以我把它定义成GetInstance()里的静态成员了

// SingletonClass::instance=nullptr;

int main(int argc, char const *argv[])
{
    // 普通类的使用
    NormalClass nc_1; // 可以实例化多个
    NormalClass* ncp_2=new NormalClass(); // 可以实例化多个
    std::cout<<&nc_1<<" ?= "<<ncp_2<<std::endl; //两个指针不一样
    delete ncp_2;
    // 单例类的使用
    // SingletonClass sc; // 单例类不能这样实例, 编译会报错
    SingletonClass* scp_1=SingletonClass::GetInstance(); // 要这样实例
    SingletonClass* scp_2=SingletonClass::GetInstance(); 
    std::cout<<scp_1<<" ?= "<<scp_2<<std::endl; //两个指针是一样的
    delete SingletonClass::GetInstance(); //用智能指针可以实现自动析构吗? 
    return 0;
}