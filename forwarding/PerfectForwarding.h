#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <type_traits>

namespace PerfectForwarding {

    void log(const std::string& s) {
        std::cout << "log(const std::string&): " << s << "\n";
    }

    void log(std::string&& s) {
        std::cout << "log(std::string&&): " << s << "\n";
    }

    // 接受一个任意类型的参数并转发给 log
    template<typename T>
    void forwardingLog(T&& msg) {
        std::cout << "forwardingLog with std::forward:\n";
        log(std::forward<T>(msg));  // 完美转发：保持左/右值特性
    }

    template<typename T>
    void movingLog(T&& msg) {
        std::cout << "movingLog with std::move:\n";
        log(std::move(msg));  // 总是转为右值（即使是左值）
    }


    class Annotation {
    public:
        explicit Annotation(const std::string text) : value(std::move(text))
        {
            //会调用拷贝构造函数 因为text的const属性没有移除 拷贝构造可以接受一个右值const 移动只接受 non-const
            //确保维持const属性的正确性。从一个对象中移动出某个值通常代表着修改该对象，所以语言不允许const对象被传递给可以修改他们的函数
        }

    private:
        std::string value;
    };


    class Demo {
    public:

        template<typename T>
        decltype(auto) user_move(T&& param)          //C++14，仍然在std命名空间
        {
            using ReturnType = std::remove_reference_t<T>&&;
            return static_cast<ReturnType>(param);
        }
        template<typename T>
        constexpr std::remove_reference_t<T>&& user_move1(T&& t) noexcept {
            return static_cast<std::remove_reference_t<T>&&>(t);
        }

        struct Widget {
            std::string name = "Widget";
        };

        void makeLogEntry(const std::string& msg, std::chrono::system_clock::time_point) {
            std::cout << msg << "\n";
        }

        void process(const Widget& lvalArg) {
            std::cout << "process(const Widget&)\n";
        }

        void process(Widget&& rvalArg) {
            std::cout << "process(Widget&&)\n";
        }

        template<typename T>
        void logAndProcess(T&& param){
            auto now = std::chrono::system_clock::now();
            makeLogEntry("Calling 'process'", now);

            // Uncomment one of the lines below to compare
            //process(param);                  //  always calls lvalue version
            process(std::forward<T>(param));  // preserves rvalue/lvalue
        }


        void run() {

            std::string test_const = "L";

            //Annotation("ssss");
            std::string lvalue = "L-value string";

            std::cout << "\n=== Direct call with lvalue ===\n";
            log(lvalue);  // 左值，调用 const& 版本

            std::cout << "\n=== Direct call with std::move ===\n";
            log(user_move(lvalue));  // 右值，调用 && 版本

            std::cout << "\n=== Forwarding log with lvalue ===\n";
            forwardingLog(lvalue);  // 保持左值，调用 const&

            std::cout << "\n=== Forwarding log with std::move(lvalue) ===\n";
            forwardingLog(user_move(lvalue));  // 保持右值，调用 &&

            std::cout << "\n=== Moving log with lvalue ===\n";
            movingLog(lvalue);  // 强制转为右值，调用 &&

            std::cout << "\n=== Moving log with rvalue ===\n";
            movingLog(std::string("R-value direct"));  // rvalue，调用 &&

            std::cout << "\n=== forward===\n";
            Widget w;
            logAndProcess(w);              // 左值：调用 const Widget& 版本
            logAndProcess(Widget{});
        }
    };
}

//Distinguish universal references from rvalue references
