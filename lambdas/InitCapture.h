#include <iostream>
#include <memory>
#include <string>
#include <functional>

namespace InitCapture {
    class Widget {
    public:
        bool isValidated() const { return false; }
        bool isProcessed() const { return false; }
        bool isArchived() const { return false; }
    private:
    };
    class Demo {
    public:

		void testLamdaCxx14() {


            auto func = [pw = std::make_unique<Widget>()]   //同之前一样
                { return pw->isValidated()          //在闭包中创建pw
                && pw->isArchived(); };


            std::cout << "[Item32::Demo] Demonstrating init-capture with move into closure\n";

            // 创建一个 std::unique_ptr，指向一个字符串
            std::unique_ptr<std::string> messagePtr(new std::string("Hello from unique_ptr!"));

            // C++14 起可以使用 init-capture，将资源通过 std::move 移入 lambda
            // 注意：外部的 messagePtr 是右值传入（std::move），内部的 msg 是捕获变量
            auto lambda = [msg = std::move(messagePtr)] {
                std::cout << "Inside lambda: " << *msg << std::endl;
                };

            // 此时 messagePtr 已被移动走，不再拥有资源
            if (!messagePtr) {
                std::cout << "messagePtr is now nullptr after move.\n";
            }

            // 调用 lambda
            lambda();

            func();

		}
        void testLamdaCxx11() {
            std::cout << "[Item32::Demo - C++11 with std::bind] Move into closure\n";

            // 使用 std::bind，并确保返回值与 std::function<void()> 兼容
            // 绑定时，使用 std::move 将 unique_ptr 传递给 lambda
            auto func = std::bind(
                [](const std::unique_ptr<std::string>& pw)
                { return false; },
                std::make_unique<std::string>()
            );
            auto bound = std::bind(
                [](const std::unique_ptr<std::string>& pw) {
                    return false;  // 此处会出错，因为 std::unique_ptr 不能通过引用捕获
                },
                std::make_unique<std::string>("Hello")
            );
            std::vector<std::string> uu{"Hello", "World", "From", "Bind"};
            auto bound1 = std::bind(
                [](const std::vector<std::string>& pw) {
                    std::cout << "Size of vector: " << pw.size() << std::endl;
                    return false;
                },
                std::move(uu)
            );

            // 调用绑定的函数对象
            func();
            bound();
            bound1();
        }

        void run() {
            testLamdaCxx14();

            testLamdaCxx11();

        }
    };

}
