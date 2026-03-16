#include <iostream>
#include <utility>
#include <string>

namespace DecltypeForwarding {

    void logAndProcess(const int& x) {
        std::cout << "[logAndProcess] const lvalue: " << x << std::endl;
    }

    void logAndProcess(int&& x) {
        std::cout << "[logAndProcess] rvalue: " << x << std::endl;
    }

    class Demo {
    public:
        void run() {
            std::cout << "[Item33::Demo] Demonstrating decltype + auto&& + std::forward\n";

            int x = 42;

            // 1. 捕获左值
            auto&& val1 = x;
            forwardIt(val1);  // 应调用 const lvalue 版本

            // 2. 捕获右值
            auto&& val2 = 100;
            forwardIt(std::move(val2));  // 应调用 rvalue 版本

            // 3. 直接 forward 右值
            forwardIt(999);  // 应调用 rvalue 版本
        }

    private:
        // 使用 decltype 来完美转发 auto&& 变量
        template <typename T>
        void forwardIt(T&& param) {
            std::cout << "[forwardIt] Forwarding with std::forward<decltype(param)>\n";
            logAndProcess(std::forward<decltype(param)>(param));
        }
    };

}
