/**
 * @file TemplateTypeDeduction.h
 * @brief 模板类型推导演示（Item 1）
 * 
 * 本文件演示了C++模板参数类型推导的规则，这是理解现代C++类型系统的基础。
 * 
 * 核心概念：
 * 1. 在模板类型推导中，引用和const限定符的处理
 * 2. 数组和函数到指针的退化
 * 3. 万能引用（T&&）的特殊推导规则
 * 
 * 类型推导规则：
 * - 参数为值传递（T param）：引用和const被忽略
 * - 参数为引用（T& param）：保留const和引用
 * - 参数为万能引用（T&& param）：根据实参类型推导
 * - 数组和函数作为实参时会退化为指针
 * 
 * @note 本Item对应《Effective Modern C++》Item 1
 */

#pragma once 
#include <iostream>
#include "../utils/type.h"

namespace TemplateTypeDeduction {
    /**
     * @brief 模板类型推导演示类
     * 
     * 本类提供了多个示例函数，演示不同的模板参数类型推导场景。
     * 每个函数都展示了特定的推导规则和注意事项。
     */
    class Demo {
    public:
        template<typename T>
        void passByValue(T param) {
            std::cout << "[passByValue] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passByRef(T& param) {
            std::cout << "[passByRef] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passByUniversalRef(T&& param) {
            std::cout << "[passByUniversalRef] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passArrayOrFunc(T param) {
            std::cout << "[passArrayOrFunc] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passArrayByRef(T& param) {
            std::cout << "[passArrayByRef] T = " << printType<T>() << "\n";
        }

        static void sampleFunction(int) {}

        void run() {
            int x = 42;
            const int cx = x;
            const int& rx = x;

            std::cout << "--- Item1: passByValue ---\n";
            passByValue(x);
            passByValue(cx);
            passByValue(rx);

            std::cout << "--- Item1: passByValue ---\n";
            const char* const ptr =         //ptr是一个常量指针，指向常量对象 
                "Fun with pointers";

            passByValue(ptr);                         //传递const char * const类型的实参

            std::cout << "--- Item1: passByRef ---\n";
            passByRef(x);
            passByRef(cx);
            passByRef(rx);

            std::cout << "--- Item1: passByUniversalRef ---\n";
            passByUniversalRef(x);
            passByUniversalRef(cx);
            passByUniversalRef(42);

            std::cout << "--- Item1: passArrayOrFunc ---\n";
            const char arr[] = "hello";
            passArrayByRef(arr);
            passArrayOrFunc(arr);
            passArrayOrFunc(&sampleFunction);  // 明确传函数指针
        }
    };
}