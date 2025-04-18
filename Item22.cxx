// Item22_PimplDemo_Impl.cpp

#include "Item22.h"  // 如果你单文件可以忽略这行

namespace Item22 {

    // 实现类定义放在 .cpp 文件中，用户不可见
    class Demo::Impl {
    public:
        void doSomething() {
            std::cout << "Item22: Doing something in Impl\n";
        }

        std::string name = "Hidden Implementation";
    };

    // 构造
    Demo::Demo()
        : pImpl(std::make_unique<Impl>()) {
    }

    // 析构
    Demo::~Demo() = default;

    // 拷贝构造
    Demo::Demo(const Demo& other)
        : pImpl(std::make_unique<Impl>(*other.pImpl)) {
    }

    // 拷贝赋值
    Demo& Demo::operator=(const Demo& other) {
        if (this != &other) {
            *pImpl = *other.pImpl;
        }
        return *this;
    }

    // 移动构造
    Demo::Demo(Demo&&) noexcept = default;

    // 移动赋值
    Demo& Demo::operator=(Demo&&) noexcept = default;

    void Demo::run() {
        pImpl->doSomething();
        std::cout << "Impl name = " << pImpl->name << "\n";
    }

} // namespace Item22
