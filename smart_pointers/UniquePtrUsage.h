#pragma once
#include <iostream>
#include <memory>
#include <string>
//默认情况，资源销毁通过delete实现，但是支持自定义删除器。有状态的删除器和函数指针会增加std::unique_ptr对象的大小
namespace UniquePtrUsage {
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
