#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <thread>

namespace TaskBasedProgramming {
    //Item 35: Prefer task - based programming to thread - based



//thread情况你需要访问非常基础的线程API。C++并发API通常是通过操作系统提供的系统级API（pthreads或者Windows threads）来实现的，系统级API通常会提供更加灵活的操作方式（举个例子，C++没有线程优先级和亲和性的概念）。为了提供对底层系统级线程API的访问，std::thread对象提供了native_handle的成员函数，而std::future（即std::async返回的东西）没有这种能力。
//你需要且能够优化应用的线程使用。举个例子，你要开发一款已知执行概况的服务器软件，部署在有固定硬件特性的机器上，作为唯一的关键进程。
//你需要实现C++并发API之外的线程技术，比如，C++实现中未支持的平台的线程池。

//
//std::thread API不能直接访问异步执行的结果，如果执行函数有异常抛出，代码会终止执行。
//基于线程的编程方式需要手动的线程耗尽、资源超额、负责均衡、平台适配性管理。
//通过带有默认启动策略的std::async进行基于任务的编程方式会解决大部分问题。
    class Demo {
    public:
        void run() {
            
        }

    private:
       
    };

}

namespace Item36 {


/* 1.任务不需要和执行get或wait的线程并行执行。
2.读写哪个线程的thread_local变量没什么问题。
3.可以保证会在std::async返回的future上调用get或wait，或者该任务可能永远不会执行也可以接受。
4.使用wait_for或wait_until编码时考虑到了延迟状态。*/



   /* std::async的默认启动策略是异步和同步执行兼有的。
        这个灵活性导致访问thread_locals的不确定性，隐含了任务可能不会被执行的意思，会影响调用基于超时的wait的程序逻辑。
        如果异步执行任务非常关键，则指定std::launch::async
        注意大多数实现（比如 MSVC、GCC）默认选择的是 launch。。*/


    
// 一个耗时任务
    int slowTask(int id) {
        std::cout << "[Task " << id << "] Started on thread: "
            << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "[Task " << id << "] Finished\n";
        return id * 10;
    }


    using namespace std::literals; // 启用 C++14 的时间字面量后缀，如 1s、100ms

    void simulateTask() {
        std::cout << "[simulateTask] Start sleeping for 1 second...\n";
        std::this_thread::sleep_for(1s); // 模拟耗时操作
        std::cout << "[simulateTask] Done sleeping.\n";
    }

   

    class Demo {
    public:

        template<typename F, typename... Ts>
        inline auto reallyAsync(F&& f, Ts&&... params)
        {
            return std::async(std::launch::async, std::forward<F>(f), std::forward<Ts>(params)...);
        }

        void testWaitForLoop() {
            std::cout << "[testWaitForLoop] Starting async task...\n";

            // 注意：没有指定 std::launch::async，有可能是延迟执行（deferred）
            auto fut = std::async(simulateTask);

            while (fut.wait_for(100ms) != std::future_status::ready) {
                std::cout << "[testWaitForLoop] Waiting...\n";
            }

            std::cout << "[testWaitForLoop] Task completed!\n";
        }

        void test_async() {
            using namespace std::chrono;

            std::cout << "=== Without specifying launch policy ===\n";
            auto start1 = steady_clock::now();
            std::future<int> f1 = std::async(slowTask, 1);  // 默认策略（可能是 async 或 deferred）
            // 主线程此处做点别的事
            auto mid1 = steady_clock::now();
            std::cout << "Main thread doing something else...\n";
            int result1 = f1.get(); // 如果是 deferred，会在这里执行 slowTask
            auto end1 = steady_clock::now();

            std::cout << "Result1: " << result1
                << ", Total time: "
                << duration_cast<seconds>(end1 - start1).count() << "s\n\n";


            std::cout << "=== With std::launch::async ===\n";
            auto start2 = steady_clock::now();
            std::future<int> f2 = std::async(std::launch::async, slowTask, 2);  // 明确异步
            std::cout << "Main thread doing something else...\n";
            std::this_thread::sleep_for(std::chrono::seconds(2));

            int result2 = f2.get();
            auto end2 = steady_clock::now();

            std::cout << "Result2: " << result2
                << ", Total time: "
                << duration_cast<seconds>(end2 - start2).count() << "s\n\n";


            std::cout << "=== With std::launch::deferred ===\n";
            auto start3 = steady_clock::now();
            std::future<int> f3 = std::async(std::launch::deferred, slowTask, 3);  // 明确延迟
            std::cout << "Main thread doing something else...\n";
            int result3 = f3.get(); // 此时才执行 slowTask（在主线程）
            auto end3 = steady_clock::now();

            std::cout << "Result3: " << result3
                << ", Total time: "
                << duration_cast<seconds>(end3 - start3).count() << "s\n";
        }
        void run() {

            //test_async();
            


            testWaitForLoop();
        }

    };

}
