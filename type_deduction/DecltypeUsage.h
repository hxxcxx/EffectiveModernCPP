#pragma once
#include <iostream>
#include <deque>
#include "../utils/type.h"

#ifdef USE_BOOST
    #include <boost/type_index.hpp>
#endif

namespace DecltypeUsage {
    class Demo {
        static int someFunc() {
            std::cout << "someFunc() called\n";
            return 42;
        }

        template<typename T1, typename T2>
        auto add(T1 a, T2 b) -> decltype(a + b) {
            return a + b;
        }


        /*容器通过传引用的方式传递非常量左值引用（lvalue - reference - to - non - const），
        因为返回一个引用允许用户可以修改容器。但是这意味着在不能给这个函数传递右值容器，
        右值不能被绑定到左值引用上（除非这个左值引用是一个const（lvalue - references - to - const），但是这里明显不是*/

        //template<typename Container, typename Index>
        //decltype(auto) authAndAccess(Container& c, Index i)
        //{
        //    return c[i];
        //}

        template<typename Container, typename Index>    //最终的C++11版本
        auto authAndAccess(Container&& c, Index i)
            -> decltype(std::forward<Container>(c)[i])
        {
            return std::forward<Container>(c)[i];
        }

        //template<typename Container, typename Index>
        //decltype(auto) authAndAccess(Container&& c, Index i)
        //{
        //    // 你可以加认证逻辑：如日志、权限验证等
        //    return std::forward<Container>(c)[i];
        //}

    public:
        void run() {
            std::cout << "--- Item3: decltype basic usage ---\n";

            int x = 10;
            int& ref = x;

            std::cout << "decltype(x): "
                << ::printType<decltype(x)>() << "\n";
            std::cout << "decltype((x)): "
                << ::printType<decltype((x))>() << "\n";
            std::cout << "decltype(ref): "
                << ::printType<decltype(ref)>() << "\n";

            std::cout << "\n--- Item3: decltype with function ---\n";
            decltype(someFunc()) val = someFunc(); // 只调用一次
            std::cout << "decltype(someFunc()) val = " << val << "\n";

            std::cout << "\n--- Item3: decltype in return type ---\n";
            auto res = add(1, 2.5);
            std::cout << "decltype(add(1, 2.5)): "
                << ::printType<decltype(res)>() << "\n";

            

            std::deque<int> d = {1, 2, 0, 0, 5, 8};
            authAndAccess(d, 5) = 10;
            std::cout << "d[5] = " << d[5] << "\n";



            std::vector<int> vec = { 1, 2, 3, 4 };

            // 左值传递
            auto& ref1 = authAndAccess(vec, 2);  // 返回引用
            std::cout << "左值引用: " << ref1 << std::endl;  // 输出 3

            // 右值传递
            auto rval_ref = authAndAccess(std::vector<int>{5, 6, 7}, 1);  // 返回右值引用
            std::cout << "右值引用: " << rval_ref << std::endl;  // 输出 6
        }
    };
}
