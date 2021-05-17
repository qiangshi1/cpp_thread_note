// 传递临时对象作为线程参数
#include <iostream>
#include <thread>
#include <string>
// #include <functional>

void a_function(const int &i, char *c, const std::string& s, const std::string& s2)
{
    std::cout << "i: " << i << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "s: " << s << std::endl;
    std::cout << "s2: " << s2 << std::endl;
}
int main(int argc, char const *argv[])
{
    int a_int = 1;
    int &a_alias = a_int;
    char a_char_array[] = "this is a test!";
    // a_int是值传递, 做了复制了, 它是安全的; a_char_array没有复制内容, 它是不安全的; a_char_array(隐式转成string)做了复制了, 但该操作是在子线程中执行的, 所以它还是不安全的; a_char_array(显式转成string)是在主线程中执行的, 它是安全的. 
    std::thread trd(a_function, a_int, a_char_array, a_char_array, std::string(a_char_array));
#define CONDITION 1
#if CONDITION == 0
    trd.join();
#elif CONDITION == 1
    trd.detach(); // 但用detach() 为什么std::cout<<"c: "<<c<<std::endl;有可能执行两次?
                  // 用detach()的话尽量不要用引用, 一定不要用指针, 建议用常量引用, 建议用显示转换
                  // 建议不使用detach()
#else

#endif
    std::cout << "this is main!" << std::endl;
    return 0;
}