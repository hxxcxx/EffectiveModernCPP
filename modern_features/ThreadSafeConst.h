#include <iostream>
#include <atomic>
#include <mutex>
#include <cmath>

namespace ThreadSafeConst {
    class Demo {
    public:
        // 示例 1：使用 std::atomic 的 const 成员函数
        struct Point {
            mutable std::atomic<int> callCount{ 0 };
            double x, y;

            Point(double xVal, double yVal) noexcept
                : x(xVal), y(yVal) {
            }

            double distanceFromOrigin() const noexcept {
                ++callCount;  // 原子递增
                return std::sqrt((x * x) + (y * y));
            }
        };

        // 示例 2：使用 mutex 的 const 成员函数（双重检查锁）
        class Widget {
        public:
            Widget() = default;

            int magicValue() const {
                // 双重检查锁以避免多次 expensive 计算
                if (!cacheValid) {
                    std::lock_guard<std::mutex> lock(m);
                    if (!cacheValid) {
                        cachedValue = expensiveComputation1() + expensiveComputation2();
                        std::cout << "Computing magicValue\n";
                        cacheValid = true;
                    }
                }
                return cachedValue;
            }

        private:
            static int expensiveComputation1() {
                // 模拟开销
                std::cout << "Computing part1...\n";
                return 42;
            }
            static int expensiveComputation2() {
                std::cout << "Computing part2...\n";
                return 58;
            }

            mutable std::mutex m;
            mutable bool cacheValid{ false };
            mutable int cachedValue{ 0 };
        };

        void run() {
            std::cout << "--- Item16: Thread Safe const Member Functions ---\n";

            // 演示 atomic 版本
            Point p(3.0, 4.0);
            std::cout << "Distance: " << p.distanceFromOrigin() << "\n";
            std::cout << "Distance: " << p.distanceFromOrigin() << "\n";
            std::cout << "Point callCount: " << p.callCount.load() << "\n";

            // 演示 mutex 版本
            Widget w;
           /* std::cout << "MagicValue first call: " << w.magicValue() << "\n";
            std::cout << "MagicValue second call: " << w.magicValue() << "\n";*/


            auto worker = [&w]() {
                for (int i = 0; i < 4; ++i) {
                    std::cout << "magicValue() = " << w.magicValue() << "\n";
                }
                };
            std::vector<std::thread> threads;
            for (int i = 0; i < 4; ++i)
                threads.emplace_back(worker);
            for (auto& t : threads) t.join();
			std::cout << "Final magicValue: " << w.magicValue() << "\n";
        }
    };
}