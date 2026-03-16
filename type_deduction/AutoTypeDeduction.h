#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include "../utils/type.h"

#ifdef USE_BOOST
    #include <boost/type_index.hpp>
#endif

namespace AutoTypeDeduction {
    class Demo {
    public:
        template<typename T>
        void f(std::initializer_list<T> initList) {
            std::cout << "[initializer_list] T = "
                << ::printType<T>()
                << ", size = " << initList.size() << "\n";
        }

       /* template<typename T>
        void f1(T param) {
            std::cout << "[by_value] T = "
                << ::printType<T>()
                << "\n";
        }*/

        void run() {
            int x = 42;
            const int cx = x;
            const int& rx = x;

            std::cout << "--- Item2: auto type deduction ---\n";

            auto a = x;   // int
            auto b = cx;  // int (顶层 const 被去掉)
            auto c = rx;  // int (引用去掉，顶层 const 被去掉)

            auto& d = x;   // int&
            auto& e = cx;  // const int&
            auto& f = rx;  // const int&

            const auto g = x;  // const int
            auto* p = &cx;     // const int*

            auto x1 = 27;                   //类型是int，值是27
            auto x2(27);                    //同上

            // auto可以推导 initializer_list
            auto x3 = { 27 };               //类型是std::initializer_list<int>，
            //值是{ 27 }
            auto x4{ 27 };                  //同上

            //auto x5 = { 1, 2, 3.0 };
            // 
            // 
          
            //f({ 11, 23, 9 });



            // 打印类型
            printType("a", a);
            printType("b", b);
            printType("c", c);
            printType("d", d);
            printType("e", e);
            printType("f", f);
            printType("g", g);
            printType("p", p);

            printType("x3", x3);
            printType("x4", x4);
            

            std::cout << "--- Item2: overload resolution with initializer list ---\n";
            //f(std::initializer_list<int>{1, 2, 3});
            //std::initializer_list<int> il = { 1, 2, 3 };
            //f(il);        // 调用 initializer_list 版本
            //f({ 42 });           // 也调用 initializer_list 版本

            //f(10);             // 调用 T by-value 版本
            //f(std::vector<int>{1, 2, 3}); // 调用 T by-value 版本
        }

    private:
        template<typename T>
        void printType(const char* name, const T& var) {
#ifdef USE_BOOST
            using boost::typeindex::type_id_with_cvr;
            std::cout << name << " : " << type_id_with_cvr<decltype(var)>().pretty_name() << "\n";
#else
            std::cout << name << " : " << ::printType<decltype(var)>() << "\n";
#endif
        }
    };
}
