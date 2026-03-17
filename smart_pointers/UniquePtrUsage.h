/**
 * @file UniquePtrUsage.h
 * @brief std::unique_ptr使用演示（Item 18）
 * 
 * 本文件演示了std::unique_ptr的使用方法，这是C++11引入的智能指针，
 * 用于管理独占所有权的资源。
 * 
 * 核心概念：
 * 1. unique_ptr独占对象所有权，不可复制，只能移动
 * 2. 支持自定义删除器，用于管理非堆内存或需要特殊清理的资源
 * 3. 与多态基类配合使用，实现工厂模式
 * 4. 内存开销小，通常等同于裸指针
 * 
 * 使用场景：
 * - 工厂函数返回对象
 * - 管理文件句柄、网络连接等资源
 * - 实现Pimpl惯用法
 * - 任何需要独占所有权的场景
 * 
 * @note 本Item对应《Effective Modern C++》Item 18
 */

#pragma once
#include <iostream>
#include <memory>
#include <string>

namespace UniquePtrUsage {
    /**
     * @brief std::unique_ptr使用演示类
     * 
     * 本类演示了unique_ptr的各种用法，包括：
     * - 基本使用方法
     * - 自定义删除器
     * - 多态基类
     * - 工厂函数
     */
    class Demo {
    public:
        // 抽象基类
        class Investment {
        public:
            Investment() = default;
            virtual ~Investment() {
                std::cout << "Investment destroyed\n";
            }
            virtual void print() const = 0;
        };

        // 派生类1
        class Stock : public Investment {
        public:
            void print() const override {
                std::cout << "Stock Investment\n";
            }
            ~Stock() { std::cout << "Stock destroyed\n"; }
        };

        // 派生类2
        class Bond : public Investment {
        public:
            void print() const override {
                std::cout << "Bond Investment\n";
            }
            ~Bond() { std::cout << "Bond destroyed\n"; }
        };

        // 派生类3
        class RealEstate : public Investment {
        public:
            void print() const override {
                std::cout << "RealEstate Investment\n";
            }
            ~RealEstate() { std::cout << "RealEstate destroyed\n"; }
        };
        struct LoggingDeleter {
            void operator()(Investment* p) const {
                std::cout << "[LoggingDeleter] Custom deleting investment...\n";
                delete p;
            }
        };
        // 工厂函数，返回 unique_ptr<Investment>
        std::unique_ptr<Investment> makeInvestment(int type) {
            switch (type) {
            case 1: return std::make_unique<Stock>();
            case 2: return std::make_unique<Bond>();
            case 3: return std::make_unique<RealEstate>();
            default: return nullptr;
            }
        }

        // 工厂函数，返回带自定义删除器的 unique_ptr
        std::unique_ptr<Investment, LoggingDeleter> makeInvestmentWithDeleter(int type) {
            switch (type) {
            case 1: return std::unique_ptr<Investment, LoggingDeleter>(new Stock());
            case 2: return std::unique_ptr<Investment, LoggingDeleter>(new Bond());
            case 3: return std::unique_ptr<Investment, LoggingDeleter>(new RealEstate());
            default: return std::unique_ptr<Investment, LoggingDeleter>(nullptr);
            }
        }

        void run() {
            std::cout << "\n--- Item18: Polymorphic UniquePtr Demo ---\n";

            auto inv = makeInvestmentWithDeleter(1);
            inv->print();

            std::unique_ptr<Investment> inv1 = makeInvestment(1);

            inv1->print();

            std::unique_ptr<Investment> inv2 = makeInvestment(2);
            inv2->print();

            std::unique_ptr<Investment> inv3 = makeInvestment(3);
            inv3->print();

            std::cout << "All investments managed by unique_ptr will auto-destroy.\n";
        }
    };
}
