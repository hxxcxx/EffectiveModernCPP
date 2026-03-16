#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <vector>
#include <functional>
//Item 40: Use std::atomic for concurrency, volatile for special memory


//std::atomic用于在不使用互斥锁情况下，来使变量被多个线程访问的情况。是用来编写并发程序的一个工具。
//volatile用在读取和写入不应被优化掉的内存上。是用来处理特殊内存的一个工具。

namespace AtomicVsVolatile {

    class Demo {
    public:
        void run() {
            std::cout << "[Item40] run() begin\n";

            std::thread consumer(&Demo::consumerThread, this);
            std::thread producer(&Demo::producerThread, this);

            consumer.join();
            producer.join();

            std::cout << "[Item40] run() end\n";
        }

    private:

        std::atomic<bool> valAvailable { false };  // 使用 std::atomic 来确保线程安全

        int computeImportantValue() {
            std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟计算延迟
            return 42;
        }

        void consumerThread() {
            // 等待 valAvailable 为 true，确保 imptValue 已准备好
            while (!valAvailable.load(std::memory_order_acquire)) {
                std::this_thread::yield();  // 给其他线程让出CPU时间
            }

            std::cout << "值已准备好，可以使用\n";
        }

        void producerThread() {
            int imptValue = computeImportantValue();
            valAvailable.store(true, std::memory_order_release);  // 设置标志，确保 imptValue 计算完成
            std::cout << "计算完成：" << imptValue << std::endl;
        }


    };

}
