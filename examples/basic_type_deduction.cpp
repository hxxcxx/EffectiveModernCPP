/**
 * @file basic_type_deduction.cpp
 * @brief 基础类型推导示例
 * 
 * 本示例演示了C++的类型推导机制，包括：
 * - 模板类型推导
 * - auto类型推导
 * - decltype类型推导
 * 
 * 编译运行:
 *   g++ -std=c++17 basic_type_deduction.cpp -o basic_type_deduction
 *   ./basic_type_deduction
 */

#include <iostream>
#include <type_traits>
#include "../utils/type.h"

/**
 * @brief 演示模板类型推导
 */
template<typename T>
void templateDeduction(T param) {
    std::cout << "模板推导 T = " << printType<T>() << "\n";
    std::cout << "参数类型 = " << printType<decltype(param)>() << "\n";
}

/**
 * @brief 演示引用的模板类型推导
 */
template<typename T>
void templateDeductionRef(T& param) {
    std::cout << "引用推导 T = " << printType<T>() << "\n";
    std::cout << "参数类型 = " << printType<decltype(param)>() << "\n";
}

/**
 * @brief 演示万能引用的模板类型推导
 */
template<typename T>
void templateDeductionUniversalRef(T&& param) {
    std::cout << "万能引用推导 T = " << printType<T>() << "\n";
    std::cout << "参数类型 = " << printType<decltype(param)>() << "\n";
}

int main() {
    std::cout << "=== 基础类型推导示例 ===\n\n";
    
    int x = 10;
    const int cx = x;
    const int& rx = x;
    
    // 1. 模板类型推导
    std::cout << "1. 模板类型推导（值传递）:\n";
    std::cout << "---------------------------\n";
    templateDeduction(x);   // T = int, param = int
    templateDeduction(cx);  // T = int, param = int (const被忽略)
    templateDeduction(rx);  // T = int, param = int (引用和const被忽略)
    
    // 2. 模板类型推导（引用传递）
    std::cout << "\n2. 模板类型推导（引用传递）:\n";
    std::cout << "-------------------------------\n";
    // templateDeductionRef(x);   // T = int, param = int&
    // templateDeductionRef(cx);  // T = const int, param = const int&
    // templateDeductionRef(rx);  // T = const int, param = const int&
    
    // 3. 万能引用推导
    std::cout << "\n3. 万能引用推导:\n";
    std::cout << "------------------\n";
    templateDeductionUniversalRef(x);   // T = int&, param = int&
    templateDeductionUniversalRef(cx);  // T = const int&, param = const int&
    templateDeductionUniversalRef(42);  // T = int, param = int&&
    
    // 4. auto类型推导
    std::cout << "\n4. auto类型推导:\n";
    std::cout << "----------------\n";
    auto a1 = x;     // auto = int
    auto a2 = cx;    // auto = int (const被忽略)
    auto a3 = rx;    // auto = int (引用被忽略)
    
    std::cout << "auto a1 = x:     " << printType<decltype(a1)>() << "\n";
    std::cout << "auto a2 = cx:    " << printType<decltype(a2)>() << "\n";
    std::cout << "auto a3 = rx:    " << printType<decltype(a3)>() << "\n";
    
    auto& a4 = x;    // auto = int, 类型为 int&
    auto& a5 = cx;   // auto = const int, 类型为 const int&
    
    std::cout << "auto& a4 = x:    " << printType<decltype(a4)>() << "\n";
    std::cout << "auto& a5 = cx:   " << printType<decltype(a5)>() << "\n";
    
    // 5. decltype类型推导
    std::cout << "\n5. decltype类型推导:\n";
    std::cout << "--------------------\n";
    decltype(x) x1 = x;      // int
    decltype((x)) x2 = x;    // int& (注意：双层括号)
    
    std::cout << "decltype(x) x1:     " << printType<decltype(x1)>() << "\n";
    std::cout << "decltype((x)) x2:   " << printType<decltype(x2)>() << "\n";
    
    return 0;
}
