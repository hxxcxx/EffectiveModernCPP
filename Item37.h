#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
#include <vector>

//Item 37: Make std::threads unjoinable on all paths

//在所有路径上保证thread最终是不可结合的。
//析构时join会导致难以调试的表现异常问题。
//析构时detach会导致难以调试的未定义行为。
//声明类数据成员时，最后声明std::thread对象。
//类成员变量的构造顺序：是按照 它们在类中声明的顺序，与你在构造函数初始化列表中的顺序无关。
//析构顺序：是构造顺序的逆序

//不可结合的std::thread对象包括：
//
//默认构造的std::threads。这种std::thread没有函数执行，因此没有对应到底层执行线程上。
//已经被移动走的std::thread对象。移动的结果就是一个std::thread原来对应的执行线程现在对应于另一个std::thread。
//已经被join的std::thread 。在join之后，std::thread不再对应于已经运行完了的执行线程。
//已经被detach的std::thread 。detach断开了std::thread对象与执行线程之间的连接。

constexpr auto tenMillion = 10000000;
// 示例：一个简单的筛选函数
bool isEven(int x) {
    return x % 2 == 0;
}
// 示例：模拟条件成立
bool conditionsAreSatisfied() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟等待
    return false;
}
// 示例：对筛选结果做某些计算
void performComputation(const std::vector<int>& vals) {
    std::cout << "Total good values: " << vals.size() << "\n";
}

namespace Item37 {
    class ThreadRAII {
    public:
        enum class DtorAction { join, detach };

        ThreadRAII(std::thread&& t, DtorAction a)
            : action(a), t(std::move(t)) {
        }

        ~ThreadRAII() {
            if (t.joinable()) {
                if (action == DtorAction::join) {
                    std::cout << "[ThreadRAII] Joining thread...\n";
                    t.join();
                }
                else {
                    std::cout << "[ThreadRAII] Detaching thread...\n";
                    t.detach();
                }
            }
        }

        std::thread& get() { return t; }

    private:
        DtorAction action;
        std::thread t;
    };

    // 示例任务：模拟一个耗时操作
    void longTask() {
        std::cout << "[Worker] Task started.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "[Worker] Task finished.\n";
    }

    void testJoinThreadRAII() {
        std::cout << "[Main] Creating joinable thread...\n";
        ThreadRAII threadRAII(
            std::thread(longTask),
            ThreadRAII::DtorAction::join
        );
        // 离开作用域时，线程将自动 join
        std::cout << "[Main] Exiting testJoinThreadRAII.\n";
    }

    void testDetachThreadRAII() {
        std::cout << "[Main] Creating detachable thread...\n";
        ThreadRAII threadRAII(
            std::thread(longTask),
            ThreadRAII::DtorAction::detach
        );
        // 离开作用域时，线程将自动 detach
        std::cout << "[Main] Exiting testDetachThreadRAII.\n";
    }


    class Demo {
    public:
        bool doWork(std::function<bool(int)> filter, int maxVal = tenMillion)
        {
            std::vector<int> goodVals;

            std::thread t([&filter, maxVal, &goodVals] {
                for (auto i = 0; i <= maxVal; ++i) {
                    if (filter(i)) {
                        goodVals.push_back(i);
                    }
                }
                });

            // 可以设置线程优先级（平台相关，这里略过）
            auto nh = t.native_handle();
            // ... 设置优先级略（例如在 Windows 可使用 SetThreadPriority）

            if (conditionsAreSatisfied()) {
                t.join();  // 等待线程完成
                performComputation(goodVals);
                return true;
            }

            //  关键点：避免“未 join 或 detach”导致 terminate
            if (t.joinable()) {
                t.detach();  // 如果不打算 join，一定要 detach
            }

            return false;
        }
        
        bool doWorkRAII(std::function<bool(int)> filter, int maxVal = tenMillion)
        {
            std::vector<int> goodVals;

            ThreadRAII t(                                   //使用RAII对象
                std::thread([&filter, maxVal, &goodVals]
                    {
                        for (auto i = 0; i <= maxVal; ++i)
                        {
                            if (filter(i)) goodVals.push_back(i);
                        }
                    }),
                ThreadRAII::DtorAction::join    //RAII动作
            );
            // 可以设置线程优先级（平台相关，这里略过）
            auto nh = t.get().native_handle();

            if (conditionsAreSatisfied()) {
                t.get().join();
                performComputation(goodVals);
                return true;
            }


			//  被 RAII 管理的线程对象会在离开作用域时自动处理
            //if (t.joinable()) {
            //    t.detach();  // 如果不打算 join，一定要 detach
            //}

            return false;
        }

        
        
        void run() {
            bool result = doWork(isEven, 100000);  // 筛选所有偶数
            std::cout << "Computation performed? " << std::boolalpha << result << "\n";


            bool resultRAII = doWorkRAII(isEven, 100000);  // 筛选所有偶数
            std::cout << "resultRAII Computation performed  ? " << std::boolalpha << resultRAII << "\n";
            

            /*longTask();
            testJoinThreadRAII();
            testDetachThreadRAII();*/
        }
    };

}