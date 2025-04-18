#include <iostream>
#include <memory>
#include <vector>
#include <stdexcept>
//std::shared_ptr for shared - ownership resource management
namespace Item19 {
    class Widget : public std::enable_shared_from_this<Widget> {
    public:
        Widget() {
            std::cout << "Widget created\n";
        }

        ~Widget() {
            std::cout << "Widget destroyed\n";
        }

        void process() {
            // 错误示例：使用裸指针构造 shared_ptr，可能导致 double delete
            // processedWidgets.emplace_back(this); //  这是错误的做法
            processedWidgets.emplace_back(shared_from_this());  // 正确做法，使用 shared_from_this()
        }

        static void example() {
            // 正确方式：创建 shared_ptr 管理 Widget 对象
            auto w = std::make_shared<Widget>();
            w->process();  // 通过 shared_ptr 调用 process 函数，正确管理内存

            // 错误方式：直接创建 Widget 对象，并尝试调用 shared_from_this()
            // Widget w2;
            // w2.process();  //  运行时会抛出 std::bad_weak_ptr 异常
        }

    private:
        std::vector<std::shared_ptr<Widget>> processedWidgets;
    };

    class Demo {
    public:
        void run() {
            try {
                std::cout << "Example 1: Correct shared_ptr usage\n";
                Widget::example();

                // 如果你尝试调用 shared_from_this() 在没有使用 shared_ptr 管理的对象上
                std::cout << "\nExample 2: Error using raw pointer\n";
                Widget w;
                w.process();  // 这会导致崩溃，抛出 bad_weak_ptr 异常

            }
            catch (const std::bad_weak_ptr& e) {
                std::cout << "Caught exception: " << e.what() << "\n";
            }
        }
    };
}

