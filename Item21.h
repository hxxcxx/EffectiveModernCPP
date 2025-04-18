#include <iostream>
#include <memory>
#include <vector>

namespace Item21 {

    struct Widget {
        int value;
        Widget(int v) : value(v) {
            std::cout << "Widget(" << value << ") constructed\n";
        }
        ~Widget() {
            std::cout << "Widget(" << value << ") destructed\n";
        }
    };

    struct CustomDeleter {
        void operator()(Widget* p) const {
            std::cout << "Custom delete Widget(" << p->value << ")\n";
            delete p;
        }
    };

    class Demo {
    public:
        void run() {
            std::cout << "--- Item21: Prefer make_unique/make_shared, with exceptions ---\n";

            //  推荐使用 make_unique
            //auto up1 = std::make_unique<Widget>(1);

            //  不能使用 make_unique 的情况：需要自定义删除器
            //std::unique_ptr<Widget, CustomDeleter> up2(new Widget(2), CustomDeleter{});

            //  不能使用 make_unique 的情况：聚合初始化
            struct Data { int x, y; };
            std::unique_ptr<Data> up3(new Data{ 10, 20 });

            //  推荐使用 make_shared
            //auto sp1 = std::make_shared<Widget>(3);

            ////  不建议使用 make_shared 的情况：
            //// 大型对象或希望提前释放内存时

            /*在 new + shared_ptr 中：
                控制块和对象分开，delete 只回收对象那一块内存
                所以更早释放对象内存，资源可控性更高*/
            std::shared_ptr<Widget> sp2(new Widget(4)); // 控制块与对象分开，释放更可控

            //  不建议 make_shared 的场景：weak_ptr 可能比 shared_ptr 活得更久
            std::weak_ptr<Widget> wp = sp2;
            sp2.reset();
            std::cout << "wp expired: " << std::boolalpha << wp.expired() << "\n";
            /*在 make_shared 中：
                控制块 + 对象 = 一整块内存（通常用 operator new 分配）
                析构对象 ≠ 立即回收整个内存，因为控制块还在被 weak_ptr 使用*/
            auto sp = std::make_shared<Widget>(4);
            std::weak_ptr<Widget> wp1 = sp;
            sp.reset();
            std::cout << "wp1 expired: " << std::boolalpha << wp1.expired() << "\n";
            //注意reset时候析构都会调用 只是申请的内存在不同的时机释放
        }
    };
}
