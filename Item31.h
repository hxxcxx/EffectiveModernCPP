#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <thread>
#include <type_traits>
#include <functional>

//Item 31: Avoid default capture modes
//C++11中有两种默认的捕获模式：按引用捕获和按值捕获。
//但默认按引用捕获模式可能会带来悬空引用的问题，
//而默认按值捕获模式可能会诱骗你让你以为能解决悬空引用的问题（实际上并没有），
//还会让你以为你的闭包是独立的（事实上也不是独立的）。

namespace Item31 {

    class Demo {
    private:
        int m_value = 42;

    public:
        void run() {
            std::cout << "\n--- Item31: Lambda capturing class members ---\n";

            // 错误方式 ：试图直接捕获成员变量（不合法）
            // auto badLambda = [m_value]() { std::cout << m_value << "\n"; }; // 错误！

            // 正确方式：捕获 this 指针
            auto lambdaWithThis = [this]() {
                std::cout << "[this] m_value = " << m_value << "\n";
                };

            // 更推荐的方式 ：复制需要的成员变量，避免悬垂 this 指针
            int localCopy = m_value;
            auto saferLambda = [localCopy]() {
                std::cout << "[copy] m_value = " << localCopy << "\n";
                };

            // 执行
            lambdaWithThis();
            saferLambda();

            // 模拟延迟执行的情况，复制是更安全的方式
            std::function<void()> delayed = saferLambda;
            std::cout << "[delayed call] ";
            delayed();
        }
    };

} // namespace Item31
