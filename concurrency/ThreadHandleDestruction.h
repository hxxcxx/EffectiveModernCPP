#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <vector>
#include <functional>
//Item 38：Be aware of varying thread handle destructor behavior


namespace ThreadHandleDestruction {

    class Demo {
    public:
        void run() {
            std::cout << "[Item38] run() begin\n";

            testFutureVectorDestructionBlocking();
            testPackagedTasks();

            std::cout << "[Item38] run() end\n";
        }

    private:

        // 示例1：future vector 析构阻塞测试
        void testFutureVectorDestructionBlocking() {
            std::cout << "\n[Future Vector Test] Begin\n";

            {
                std::vector<std::future<void>> futs;

                for (int i = 0; i < 3; ++i) {
                    futs.emplace_back(std::async(std::launch::async, [i] {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        std::cout << "Task " << i << " done\n";
                        }));
                }

                std::cout << "Tasks launched. Leaving scope...\n";
                // 注意：没有显式调用 get/wait，析构时会阻塞等待所有 future 完成
            }

            std::cout << "[Future Vector Test] All futures destroyed\n";
        }

        // 示例2：使用 packaged_task 封装不同任务
        void testPackagedTasks() {
            std::cout << "\n[Packaged Task Test] Begin\n";

            // 定义不同的任务函数
            auto workA = [] {
                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                std::cout << "Task A done\n";
                };

            auto workB = [] {
                std::this_thread::sleep_for(std::chrono::milliseconds(300));
                std::cout << "Task B done\n";
                };

            auto workC = [] {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Task C done\n";
                };

            // 封装为 packaged_task
            std::packaged_task<void()> taskA(workA);
            std::packaged_task<void()> taskB(workB);
            std::packaged_task<void()> taskC(workC);

            // 取出 future，用于同步等待
            auto futA = taskA.get_future();
            auto futB = taskB.get_future();
            auto futC = taskC.get_future();

            // 启动线程执行任务
            std::thread(std::move(taskA)).detach();
            std::thread(std::move(taskB)).detach();
            std::thread(std::move(taskC)).detach();

            futA.wait();
            futB.wait();
            futC.wait();

            std::cout << "[Packaged Task Test] All tasks finished\n";
        }
    };

}
