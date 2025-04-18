#include <iostream>
#include <type_traits>

namespace Item17 {
    class Demo {
    public:
        struct A {
            // 什么都不写，默认会生成拷贝 & 移动构造
        };

        struct B {
            B(const B&) = default;  // 显式声明拷贝构造
        };

        struct C {
            ~C() = default;         // 显式声明析构函数
        };
        struct B2 {
            B2(const B2&) { std::cout << "copy ctor\n"; }  // 自定义拷贝构造函数
        };

        struct C2 {
            ~C2() { std::cout << "custom dtor\n"; }        // 自定义析构函数
        };
        struct D {
            D(const D&) = default;
            D(D&&) = default;
            D& operator=(const D&) = default;
            D& operator=(D&&) = default;
            ~D() = default;
        };

        template<typename T>
        void printTraits(const std::string& name) {
            std::cout << name
                << ": move_constructible = " << std::boolalpha
                << std::is_move_constructible<T>::value
                << ", move_assignable = "
                << std::is_move_assignable<T>::value
                << "\n";
        }

        void run() {
            std::cout << "--- Item17: Special Member Functions ---\n";
            printTraits<A>("A (implicit default)");
            printTraits<B>("B (user-defined copy ctor)");
            printTraits<C>("C (user-defined dtor)");
            printTraits<B2>("B2 (user-defined copy ctor)");
            printTraits<C2>("C2 (user-defined dtor)");
            printTraits<D>("D (all special functions defaulted)");
        }
    };
}
