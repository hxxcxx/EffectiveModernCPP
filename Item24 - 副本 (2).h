#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <thread>
#include <type_traits>

namespace Item24 {
    //template<class T, class Allocator = allocator<T>>   //来自C++标准
    //class vector
    //{
    //public:
    //    void push_back(T&& x);
    //}

    //push_back函数的形参当然有一个通用引用的正确形式，然而，在这里并没有发生类型推导。
    //因为push_back在有一个特定的vector实例之前不可能存在，而实例化vector时的类型已经决定了


    //template<class T, class Allocator = allocator<T>>   //依旧来自C++标准
    //class vector {
    //public:
    //    template <class... Args>//Args实际上是一个parameter pack
    //    void emplace_back(Args&&... args); //通用引用
    //    …
    //};

    //class Demo {
    //public:
    //    // 一个测试函数，接受左值引用
    //    void greet(const std::string& name) {
    //        std::cout << "Hello, " << name << std::endl;
    //    }

    //    // 一个模拟计算的函数，带右值参数
    //    int slowAdd(int a, int b) {
    //        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //        return a + b;
    //    }

    //    void run() {
    //        // C++17 通用计时 Lambda
    //        auto timeFuncInvocation = [](auto&& func, auto&&... params) -> decltype(auto) {
    //            auto start = std::chrono::high_resolution_clock::now();

    //            // 正确使用 decltype(auto) 和完美转发
    //            decltype(auto) result = std::forward<decltype(func)>(func)(
    //                std::forward<decltype(params)>(params)...);

    //            auto end = std::chrono::high_resolution_clock::now();
    //            auto duration = std::chrono::duration<double, std::milli>(end - start);
    //            std::cout << "Elapsed time: " << duration.count() << " ms\n";

    //            return result;
    //            };

    //        std::string name = "Alice";
    //        auto greetLambda = [](const std::string& s) {
    //            std::cout << "Hello, " << s << std::endl;
    //            };

    //        timeFuncInvocation(greetLambda, name); // 正常
    //        //int result = timeFuncInvocation(slowAdd, 10, 20);  // 传右值
    //        std::cout << "Result of slowAdd: " << result << std::endl;
    //    }
    //};

}
//Use std::move on rvalue references, std::forward on universal references 25

//如果对从按值返回的函数返回来的局部对象使用std::move，
//你并不能帮助编译器（如果不能实行拷贝消除的话，他们必须把局部对象看做右值），
//而是阻碍其执行优化选项（通过阻止RVO）。在某些情况下，
//将std::move应用于局部变量可能是一件合理的事（即，你把一个变量传给函数，并且知道不会再用这个变量）
//，但是满足RVO的return语句或者返回一个传值形参并不在此列。


//Avoid overloading on universal references 26
//对通用引用形参的函数进行重载，通用引用函数的调用机会几乎总会比你期望的多得多。
//完美转发构造函数是糟糕的实现，因为对于non - const左值，它们比拷贝构造函数而更匹配，
//而且会劫持派生类对于基类的拷贝和移动构造函数的调用。