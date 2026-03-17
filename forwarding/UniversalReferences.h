/**
 * @file UniversalReferences.h
 * @brief 通用引用演示（Item 24）
 * 
 * 本文件演示了通用引用（Universal References）的概念和使用。
 * 
 * 核心概念：
 * 1. 通用引用的形式：T&&（其中T需要推导）
 * 2. 通用引用可以绑定到左值和右值
 * 3. 右值引用的形式：T&&（其中T不需要推导）
 * 4. 区分通用引用和右值引用很重要
 * 
 * 通用引用vs右值引用：
 * - 通用引用：T&&，T需要推导（如模板参数、auto）
 * - 右值引用：T&&，T不需要推导（如已知的类型）
 * 
 * 使用场景：
 * - 模板函数参数
 * - auto变量声明
 * - 完美转发
 * 
 * @note 本Item对应《Effective Modern C++》Item 24
 */

#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <thread>
#include <type_traits>

namespace UniversalReferences {
    /**
     * @brief 通用引用演示类
     * 
     * 本类演示了通用引用的各种使用场景和注意事项。
     */
    class Demo {
    public:
        /**
         * @brief 接受左值引用的函数
         */
        void greet(const std::string& name) {
            std::cout << "Hello, " << name << std::endl;
        }

        /**
         * @brief 模拟计算的函数，带右值参数
         */
        int slowAdd(int a, int b) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            return a + b;
        }

        /**
         * @brief 演示通用引用的基本用法
         */
        void demoBasicUniversalRef() {
            std::cout << "\n=== 通用引用基本用法 ===\n";
            
            // 通用引用在模板中
            auto process = [](auto&& x) {
                std::cout << "处理值: " << x << "\n";
            };
            
            int x = 10;
            process(x);      // 左值
            process(20);     // 右值
        }

        /**
         * @brief 演示通用引用与右值引用的区别
         */
        void demoUniversalVsRvalueRef() {
            std::cout << "\n=== 通用引用 vs 右值引用 ===\n";
            
            // 通用引用（T需要推导）
            auto universalRefLambda = [](auto&& x) {
                std::cout << "通用引用: " << x << "\n";
            };
            
            // 右值引用（T不需要推导）
            auto rvalueRefLambda = [](int&& x) {
                std::cout << "右值引用: " << x << "\n";
            };
            
            int x = 10;
            
            // 通用引用可以接受左值
            universalRefLambda(x);      // OK
            universalRefLambda(20);     // OK
            
            // 右值引用只能接受右值
            // rvalueRefLambda(x);      // 错误！不能绑定左值
            rvalueRefLambda(20);        // OK
        }

        /**
         * @brief 演示完美转发
         */
        void demoPerfectForwarding() {
            std::cout << "\n=== 完美转发演示 ===\n";
            
            // 通用计时Lambda（C++17）
            auto timeFuncInvocation = [](auto&& func, auto&&... params) -> decltype(auto) {
                auto start = std::chrono::high_resolution_clock::now();

                // 正确使用 decltype(auto) 和完美转发
                decltype(auto) result = std::forward<decltype(func)>(func)(
                    std::forward<decltype(params)>(params)...);

                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration<double, std::milli>(end - start);
                std::cout << "耗时: " << duration.count() << " ms\n";

                return result;
            };

            // 测试函数
            auto greetLambda = [](const std::string& s) {
                std::cout << "Hello, " << s << "\n";
                return std::string("Greeted: ") + s;
            };

            std::string name = "Alice";
            auto result = timeFuncInvocation(greetLambda, name);
            std::cout << "结果: " << result << "\n";
        }

        /**
         * @brief 演示std::forward的正确使用
         */
        void demoStdForward() {
            std::cout << "\n=== std::forward演示 ===\n";
            
            auto processValue = [](auto&& value) {
                // 使用std::forward保持值类别
                std::cout << "处理: " << std::forward<decltype(value)>(value) << "\n";
            };
            
            std::string str = "Hello";
            processValue(str);       // 左值
            processValue("World");   // 右值
        }

        /**
         * @brief 运行所有演示
         */
        void run() {
            std::cout << "=== Item 24: 通用引用演示 ===\n";
            
            demoBasicUniversalRef();
            demoUniversalVsRvalueRef();
            demoPerfectForwarding();
            demoStdForward();
            
            std::cout << "\n=== 演示完成 ===\n";
        }
    };
}

// Item 25: Use std::move on rvalue references, std::forward on universal references
// 对右值引用使用std::move，对通用引用使用std::forward

// Item 26: Avoid overloading on universal references
// 避免对通用引用进行重载
// 对通用引用形参的函数进行重载，通用引用函数的调用机会几乎总会比你期望的多得多。
// 完美转发构造函数是糟糕的实现，因为对于non-const左值，它们比拷贝构造函数更匹配，
// 而且会劫持派生类对于基类的拷贝和移动构造函数的调用。