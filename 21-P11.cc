// std::future std::async
#include <iostream>
#include <unistd.h> // sleep
#include <future>   // std::future std::async std::launch. future已经包含了thread

int a_func()
{
    std::cout << "this is a func!: "<<std::this_thread::get_id()<< std::endl;
    sleep(5);
    return 5;
}

class AC
{
public:
    int a_class_func(int a_int)
    {
        std::cout << "this is a class func!: " <<std::this_thread::get_id()<< std::endl;
        a_int++;
        sleep(5);
        return a_int;
    }
};

int main(int argc, char const *argv[])
{
    std::cout << "this is main start!: "<<std::this_thread::get_id() << std::endl;
#define CONDITION 3
#if CONDITION == 0
    // 1. 普通函数用作线程的情况
    std::future<int> result1 = std::async(a_func);            // 这步在创建线程并执行
    std::cout << "1. result: " << result1.get() << std::endl; // 系统会卡在result.get(), 直到线程返回
// std::cout<<"result: "<<result.get()<<std::endl; // 不能多次使用result.get(), 运行时报错
// result.wait(), 等线程执行完毕. 不返回值
#elif CONDITION == 1
    // 2. 类成员函数用作线程的情况
    AC ac;
    int a_int = 10;
    std::future<int> result2 = std::async(&AC::a_class_func, &ac, a_int);
    std::cout << "2. result: " << result2.get() << std::endl;
#elif CONDITION == 2
    //3. std::future+std::launch::deferred
    //std::launch是一个枚举类型, 在std::asyc()的第一个形参处加入
    //std::launch::deferred是延迟创建线程, 表示线程在std::async(std::launch::deferred, a_func)处只声明, 在result3.get()处才执行. 
    // 如果不调用result3.get(), 线程不会执行
    // 经过实际测试, 好像std::launch::deferred并不会创建子线程. ----确实不会创建新线程, 老师在P13 20min讲到. 
    std::future<int> result3 = std::async(std::launch::deferred, a_func);         
    std::cout << "3. result: " << result3.get() << std::endl; 
#elif CONDITION == 3
    //3. std::future+std::launch::async 
    //std::async(std::launch::async, a_func)等价于std::async(a_func)    
    //相当于std::launch::async是默认参数
    std::future<int> result4 = std::async(std::launch::async, a_func);         
    std::cout << "4. result: " << result4.get() << std::endl; 
#else
#endif // CONDITION
    std::cout << "this is main end!:"<<std::this_thread::get_id() << std::endl;
    return 0;
}