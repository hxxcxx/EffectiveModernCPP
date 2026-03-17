/**
 * @file lambda_basics.cpp
 * @brief Lambda表达式基础示例
 * 
 * 本示例演示了C++ Lambda表达式的基本用法：
 * - Lambda语法
 * - 捕获模式
 * - 初始化捕获（C++14）
 * - 泛型Lambda（C++14）
 * 
 * 编译运行:
 *   g++ -std=c++17 lambda_basics.cpp -o lambda_basics
 *   ./lambda_basics
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

/**
 * @brief 演示Lambda的基本语法
 */
void demoBasicLambda() {
    std::cout << "\n=== Lambda基本语法 ===\n";
    
    // 最简单的Lambda
    auto hello = []() {
        std::cout << "Hello, Lambda!\n";
    };
    hello();
    
    // 带参数的Lambda
    auto add = [](int a, int b) {
        return a + b;
    };
    std::cout << "3 + 4 = " << add(3, 4) << "\n";
    
    // 指定返回类型
    auto divide = [](int a, int b) -> double {
        if (b == 0) return 0.0;
        return static_cast<double>(a) / b;
    };
    std::cout << "10 / 3 = " << divide(10, 3) << "\n";
}

/**
 * @brief 演示Lambda的捕获模式
 */
void demoCaptureModes() {
    std::cout << "\n=== Lambda捕获模式 ===\n";
    
    int x = 10;
    int y = 20;
    
    // 值捕获
    auto captureByValue = [x]() {
        std::cout << "值捕获 x = " << x << "\n";
    };
    captureByValue();
    
    // 引用捕获
    auto captureByRef = [&x]() {
        x = 100;  // 可以修改外部变量
        std::cout << "引用捕获 x = " << x << "\n";
    };
    captureByRef();
    std::cout << "外部 x = " << x << "\n";
    
    // 隐式捕获（所有变量按值捕获）
    auto implicitCaptureByValue = [=]() {
        std::cout << "隐式值捕获 x = " << x << ", y = " << y << "\n";
    };
    implicitCaptureByValue();
    
    // 隐式捕获（所有变量按引用捕获）
    auto implicitCaptureByRef = [&]() {
        std::cout << "隐式引用捕获 x = " << x << ", y = " << y << "\n";
    };
    implicitCaptureByRef();
    
    // 混合捕获
    auto mixedCapture = [x, &y]() {
        std::cout << "混合捕获 x = " << x << ", y = " << y << "\n";
        y = 200;  // 可以修改引用捕获的变量
    };
    mixedCapture();
    std::cout << "外部 y = " << y << "\n";
}

/**
 * @brief 演示可变Lambda（mutable）
 */
void demoMutableLambda() {
    std::cout << "\n=== 可变Lambda（mutable） ===\n";
    
    int x = 10;
    
    // 默认情况下，值捕获的变量是只读的
    // auto lambda1 = [x]() {
    //     x = 20;  // 错误！不能修改值捕获的变量
    // };
    
    // 使用mutable关键字允许修改值捕获的变量
    auto lambda2 = [x]() mutable {
        x = 20;  // OK，但只影响Lambda内部的副本
        std::cout << "Lambda内部 x = " << x << "\n";
    };
    lambda2();
    std::cout << "外部 x = " << x << "（未改变）\n";
}

/**
 * @brief 演示初始化捕获（C++14）
 */
void demoInitCapture() {
    std::cout << "\n=== 初始化捕获（C++14） ===\n";
    
    auto ptr = std::make_unique<int>(42);
    
    // 移动捕获
    auto lambda = [p = std::move(ptr)]() {
        std::cout << "捕获的值: " << *p << "\n";
    };
    lambda();
    
    // ptr现在为nullptr
    if (!ptr) {
        std::cout << "ptr已被移动\n";
    }
    
    // 捕获并转换
    std::string name = "Alice";
    auto lambda2 = [name = std::move(name)]() {
        std::cout << "Name: " << name << "\n";
    };
    lambda2();
}

/**
 * @brief 演示泛型Lambda（C++14）
 */
void demoGenericLambda() {
    std::cout << "\n=== 泛型Lambda（C++14） ===\n";
    
    // 使用auto参数
    auto print = [](auto value) {
        std::cout << "值: " << value << "\n";
    };
    
    print(42);
    print(3.14);
    print("Hello");
    
    // 多个auto参数
    auto add = [](auto a, auto b) {
        return a + b;
    };
    
    std::cout << "3 + 4 = " << add(3, 4) << "\n";
    std::cout << "3.5 + 2.5 = " << add(3.5, 2.5) << "\n";
}

/**
 * @brief 演示Lambda与STL算法结合使用
 */
void demoLambdaWithSTL() {
    std::cout << "\n=== Lambda与STL算法 ===\n";
    
    std::vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // 使用std::sort和Lambda
    std::sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;
    });
    
    std::cout << "排序后: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";
    
    // 使用std::find_if和Lambda
    auto it = std::find_if(numbers.begin(), numbers.end(), [](int n) {
        return n > 5;
    });
    
    if (it != numbers.end()) {
        std::cout << "第一个大于5的数: " << *it << "\n";
    }
    
    // 使用std::for_each和Lambda
    std::cout << "所有偶数: ";
    std::for_each(numbers.begin(), numbers.end(), [](int n) {
        if (n % 2 == 0) {
            std::cout << n << " ";
        }
    });
    std::cout << "\n";
}

/**
 * @brief 演示Lambda作为返回值
 */
void demoLambdaAsReturnValue() {
    std::cout << "\n=== Lambda作为返回值 ===\n";
    
    // 返回Lambda
    auto makeMultiplier = [](int factor) {
        return [factor](int x) {
            return x * factor;
        };
    };
    
    auto times3 = makeMultiplier(3);
    auto times5 = makeMultiplier(5);
    
    std::cout << "10 * 3 = " << times3(10) << "\n";
    std::cout << "10 * 5 = " << times5(10) << "\n";
}

int main() {
    std::cout << "=== Lambda表达式基础示例 ===\n";
    
    demoBasicLambda();
    demoCaptureModes();
    demoMutableLambda();
    demoInitCapture();
    demoGenericLambda();
    demoLambdaWithSTL();
    demoLambdaAsReturnValue();
    
    std::cout << "\n=== 示例完成 ===\n";
    
    return 0;
}
