#include <iostream>
#include <thread>
#include <future>
#include <condition_variable>
#include <chrono>

namespace EventNotification {
    //相对完美的方案 std::promise只能设置一次。std::promise和future之间的通信是一次性的
    class DemoPromise {
    public:
        void run() {
            std::cout << "[Item39] run() begin\n";

            std::promise<void> taskDonePromise;    // 用 promise 创建共享状态
            std::future<void> taskDoneFuture = taskDonePromise.get_future();  // 获取对应的 future

            std::condition_variable cv;
            std::mutex mtx;

            // 反应任务：等待事件通知
            auto reactingTask = [&cv, &mtx, &taskDoneFuture] {
                std::cout << "Reacting task waiting for event...\n";
                taskDoneFuture.wait();  // 等待 future 变为 ready（任务完成）
                std::cout << "Reacting task responded to the event.\n";
                };

            // 检测任务：模拟一些检查，完成后通知反应任务
            auto detectingTask = [&cv, &mtx, &taskDonePromise] {
                std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟一些工作
                std::cout << "Detecting task finished work.\n";
                taskDonePromise.set_value();  // 设置 promise，通知反应任务
                };

            // 启动反应任务和检测任务
            std::thread reactThread(reactingTask);
            std::thread detectThread(detectingTask);

            // 等待两个线程完成
            detectThread.join();
            reactThread.join();
            std::cout << "[Item39] run() end\n";
        }
    };
    //受虚假唤醒的影响
    class DemoCV {
    public:
        void run() {
            std::thread reactThread(&DemoCV::reactingTask, this);
            std::thread detectThread(&DemoCV::detectingTask, this);

            reactThread.join();
            detectThread.join();
        }

    private:
        std::condition_variable cv; // 用于事件通知
        std::mutex m;               // 用于保护共享状态
        bool eventHappened = false; // 共享状态变量

        void reactingTask() {
            std::cout << "[Reacting] 等待事件...\n";
            std::unique_lock<std::mutex> lock(m);
            // 等待直到 eventHappened 为 true
            cv.wait(lock, [this] { return eventHappened; });

            std::cout << "[Reacting] 收到事件通知！继续执行。\n";
        }

        void detectingTask() {
            std::cout << "[Detecting] 检测中...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            {
                std::lock_guard<std::mutex> lock(m);
                eventHappened = true; // 设置事件已发生
            }

            std::cout << "[Detecting] 事件已发生，通知等待者。\n";
            cv.notify_one(); // 通知一个等待的线程
        }
    };
    //有切换开销
    class DemoFlag {
    public:
        void run() {
            std::thread reactThread(&DemoFlag::reactingTask, this);
            std::thread detectThread(&DemoFlag::detectingTask, this);

            reactThread.join();
            detectThread.join();
        }

    private:
        std::atomic<bool> readyFlag{ false }; // 原子标志位，初始为 false

        void detectingTask() {
            std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟任务处理

            std::cout << "[Detecting Task] 任务完成，设置标志位。\n";
            readyFlag.store(true); // 设置为 true，表示已准备好
        }

        void reactingTask() {
            std::cout << "[Reacting Task] 等待检测任务完成...\n";

            // 自旋等待直到 readyFlag 为 true
            while (!readyFlag.load()) {
                std::this_thread::yield(); // 避免过度占用CPU, 
                //低优先级线程 或者 自旋等待
            }

            //std::this_thread::yield() 确实有上下文切换的开销，但它比主动阻塞线程（如 std::this_thread::sleep_for()）的开销要小一些。

            /*当线程调用 std::this_thread::yield() 时，它会主动告诉操作系统当前线程不再需要占用 CPU 时间片，操作系统可能会将 CPU 时间片分配给其他线程。
            操作系统进行上下文切换时，会保存当前线程的状态，加载另一个线程的状态，这个过程会涉及一些内存操作和 CPU 寄存器的切换，因此会有一定的开销。*/

            std::cout << "[Reacting Task] 收到信号，开始处理任务！\n";
        }

    };
}
