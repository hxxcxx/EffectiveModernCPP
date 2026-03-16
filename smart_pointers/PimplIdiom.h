// Item22_PimplDemo.cpp

#include <iostream>
#include <memory>
#include <string>

namespace PimplIdiom {

    class Demo {
    public:
        Demo();
        ~Demo();

        Demo(const Demo&);             // 拷贝构造
        Demo& operator=(const Demo&);  // 拷贝赋值
        Demo(Demo&&) noexcept;         // 移动构造
        Demo& operator=(Demo&&) noexcept; // 移动赋值

        void run(); // 对外接口函数

    private:
        class Impl;                  // 前向声明
        std::unique_ptr<Impl> pImpl; // 实现细节隐藏
    };

} // namespace Item22
