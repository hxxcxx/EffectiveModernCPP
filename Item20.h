#include <iostream>
#include <memory>
#include <vector>

namespace Item20 {
    class Widget : public std::enable_shared_from_this<Widget> {
    public:
        void addConnection(std::shared_ptr<Widget> target) {
            // 保存的是 weak_ptr，避免循环引用
            connections.emplace_back(target);
        }

        void showConnections() const {
            std::cout << "Connections: ";
            for (const auto& wptr : connections) {
                if (auto sp = wptr.lock()) {
                    std::cout << "[Connected] ";
                }
                else {
                    std::cout << "[Expired] ";
                }
            }
            std::cout << "\n";
        }

    private:
        std::vector<std::weak_ptr<Widget>> connections;
    };

    class Demo {
    public:
        void run() {
            std::cout << "--- Item20: Use weak_ptr for possibly dangling shared_ptr ---\n";

            std::shared_ptr<Widget> w1 = std::make_shared<Widget>();
            std::shared_ptr<Widget> w2 = std::make_shared<Widget>();

            w1->addConnection(w2);  // w1 持有 w2 的弱引用

            w1->showConnections();  // 显示 w2 尚未释放

            w2.reset();             // 手动释放 w2
            w1->showConnections();  // 现在 w2 是 expired
        }
    };
}
