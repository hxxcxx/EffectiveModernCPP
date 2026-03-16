#include <iostream>
#include <array>
#include <type_traits>
//Use constexpr whenever possible
//
//
//constexpr对象是const，它被在编译期可知的值初始化
//当传递编译期可知的值时，constexpr函数可以产出编译期可知的结果
//constexpr对象和函数可以使用的范围比non - constexpr对象和函数要大
//constexpr是对象和函数接口的一部分

namespace ConstexprUsage {
    class Demo {
    public:
        // 示例 1：constexpr 递归计算阶乘（C++11）
        static constexpr int factorial(int n) {
            return n <= 1 ? 1 : (n * factorial(n - 1));
        }

        // 示例 2：constexpr 获取数组大小
        template<typename T, std::size_t N>
        static constexpr std::size_t arraySize(T(&)[N]) noexcept {
            return N;
        }

        // 示例 3：constexpr 类和成员函数（C++11）
        struct Point {
            int x, y;
            constexpr Point(int xVal = 0, int yVal = 0) noexcept : x(xVal), y(yVal) {}
            constexpr int sum() const noexcept { return x + y; }
        };

        // 示例 4：C++14 中更灵活的 constexpr（支持循环）
        static constexpr int fib(int n) {
            int a = 0, b = 1;
            for (int i = 0; i < n; ++i) {
                int tmp = a + b;
                a = b;
                b = tmp;
            }
            return a;
        }

        static int constexpr add(int a, int b) noexcept {
            return a + b;
        }
        /*static int add(int a, int b) noexcept {
            return a + b;
        }*/

        void run() {
            std::cout << "--- Item15: constexpr Demo ---\n";

            // 编译时计算 factorial
            constexpr int f5 = factorial(5);
            static_assert(f5 == 120, "factorial(5) must be 120");
            std::cout << "factorial(5) = " << f5 << "\n";

            // constexpr 模板函数 arraySize
            int arr[10] = {};
            constexpr std::size_t sz = arraySize(arr);
            std::cout << "array size = " << sz << "\n";

            // constexpr 类 Point
            constexpr Point p(3, 4);
            static_assert(p.sum() == 7, "Point sum must be 7");
            std::cout << "Point sum = " << p.sum() << "\n";

            // C++14 constexpr Fibonacci
            constexpr int f7 = fib(7);
            static_assert(f7 == 13, "fib(7) must be 13");
            std::cout << "fib(7) = " << f7 << "\n";


            // constexpr 接口示例
            constexpr int sum = add(2, 3);
            static_assert(sum == 5, "add(2,3) must be 5");
            std::cout << "add(2,3) = " << sum << "";
        }
    };
}