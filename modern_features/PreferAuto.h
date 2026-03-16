#pragma once
#include <iostream>
#include <functional>
#include <chrono>
#include <deque>
//不可见的代理类通常不适用于auto。
namespace PreferAuto {
    class Demo {
    public:
        void compareAutoVsStdFunction() {
            constexpr int LOOP = 10000000;
            int x = 1;

            // auto 声明的 lambda
            auto autoLambda = [x]() { return x + 1; };

            // std::function 声明的 lambda（类型擦除 + 可能堆分配）
            std::function<int()> stdFunc = [x]() { return x + 1; };

            // 测试 auto lambda
            auto start1 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < LOOP; ++i) autoLambda();
            auto end1 = std::chrono::high_resolution_clock::now();

            // 测试 std::function lambda
            auto start2 = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < LOOP; ++i) stdFunc();
            auto end2 = std::chrono::high_resolution_clock::now();

            std::chrono::duration<double> durationAuto = end1 - start1;
            std::chrono::duration<double> durationStd = end2 - start2;

            std::cout << "[auto lambda]       Time: " << durationAuto.count() << " s\n";
            std::cout << "[std::function lambda] Time: " << durationStd.count() << " s\n";
        }

        void run() {
            std::deque<int> values = { 10, 20, 30, 40, 50 };

            //显式类型声明太冗长，容易出错
            std::deque<int>::const_iterator it1 = values.begin();

            //使用 auto，简洁且更不易出错
            auto it2 = values.begin();

            std::cout << "Using explicit type: " << *it1 << std::endl;
            std::cout << "Using auto: " << *it2 << std::endl;

            //显式类型声明，容易因类型不一致导致问题
            std::deque<int>::iterator it3 = values.begin(); // 如果 values 是 const，会报错

            // 用 auto 可以自动推导出 const_iterator 或 iterator
            for (auto it = values.begin(); it != values.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;

            //使用 auto 遍历元素，简洁安全
            for (const auto& val : values) {
                std::cout << val << " ";
            }
            std::cout << std::endl;

            //测试闭包
            compareAutoVsStdFunction();
        }
    };
}
