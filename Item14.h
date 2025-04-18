#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <utility>
//Declare functions noexcept if they won’t emit exceptions
class MyClass {
public:
    MyClass() = default;
    MyClass(MyClass&&) noexcept {
        std::cout << "MyClass move ctor called\n";
    }
};

struct Bad {
    ~Bad() noexcept(false) {}
};

namespace Item14 {
    class Demo {
    public:
        // 简单的 noexcept 函数
        static void f1() noexcept {
            // 不会抛异常
        }

        static void f2() {
            // 可能抛异常
        }

        // 条件 noexcept：仅当 std::swap(a, b) 不抛时才 noexcept
        template<typename T>
        static void swapNoexcept(T& a, T& b) noexcept(noexcept(std::swap(a, b))) {
            std::swap(a, b);
        }

        void run() {
            std::cout << std::boolalpha;

            std::cout << "f1 is noexcept: " << noexcept(f1()) << "\n";
            std::cout << "f2 is noexcept: " << noexcept(f2()) << "\n";

            int a = 1, b = 2;
            swapNoexcept(a, b);
            std::cout << "swapNoexcept<int> is noexcept: "
                << noexcept(swapNoexcept<int>(a, b)) << "\n";

            std::cout << "MyClass move ctor is noexcept: "
                << noexcept(MyClass(std::declval<MyClass>())) << "\n";

            std::cout << "vector<MyClass> is_nothrow_move_constructible: "
                << std::is_nothrow_move_constructible<MyClass>::value << "\n";

            std::cout << "Bad destructor noexcept: "
                << noexcept(std::declval<Bad>().~Bad()) << "\n";
        }
    };
}