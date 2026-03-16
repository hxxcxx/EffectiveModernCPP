#pragma once
#include <iostream>
#include <memory>
#include <mutex>
//Prefer nullptr to 0 and NULL
namespace PreferNullptr {

    struct Widget {};

    int f1(std::shared_ptr<Widget> spw) {
        std::cout << "f1 called with shared_ptr\n";
        return 1;
    }

    double f2(std::unique_ptr<Widget> upw) {
        std::cout << "f2 called with unique_ptr\n";
        return 2.0;
    }

    bool f3(Widget* pw) {
        std::cout << "f3 called with raw pointer\n";
        return true;
    }
    using MuxGuard = std::lock_guard<std::mutex>;
    template<typename FuncType, typename MuxType, typename PtrType>
    decltype(auto) lockAndCall(FuncType func, MuxType& mutex, PtrType ptr)
    {
        MuxGuard g(mutex);
        return func(ptr);
    }

    class Demo {
    public:
        void run() {
            std::cout << "Calling f1, f2, f3 with nullptr:\n";

            f1(nullptr);  // 正确，shared_ptr 可以从 nullptr 构造
            f2(nullptr);  // 正确，unique_ptr 也可以从 nullptr 构造
            f3(nullptr);  // 正确，裸指针直接匹配 nullptr

            std::cout << "\nCalling f3 with 0 and NULL (dangerous in overloads):\n";

            // f3(0);       //  可以工作，但可能导致重载歧义（0 是 int）
            // f3(NULL);    // 也可以工作，但 NULL 可能是 0，存在同样风险

            // f1(0);      //  编译错误：不能从 int 构造 shared_ptr
            // f2(0);      //  编译错误：不能从 int 构造 unique_ptr
            std::mutex f1m, f2m, f3m;

            //auto result1 = lockAndCall(f1, f1m, 0);
            //auto result2 = lockAndCall(f2, f2m, NULL);      //错误！
            auto result3 = lockAndCall(f2, f3m, nullptr);   //没问题
        }
    };
}
