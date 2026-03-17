// Effective-Modern-CPP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <map>
#include <vector>

// 类型推导
#include "type_deduction/TemplateTypeDeduction.h"
#include "type_deduction/AutoTypeDeduction.h"
#include "type_deduction/DecltypeUsage.h"

// 现代特性
#include "modern_features/PreferAuto.h"
#include "modern_features/BraceInitialization.h"
#include "modern_features/PreferNullptr.h"
#include "modern_features/ScopedEnums.h"
#include "modern_features/NoexceptFunctions.h"
#include "modern_features/ConstexprUsage.h"
#include "modern_features/ThreadSafeConst.h"
#include "modern_features/SpecialMemberFunctions.h"

// 智能指针
#include "smart_pointers/UniquePtrUsage.h"
#include "smart_pointers/SharedPtrUsage.h"
#include "smart_pointers/WeakPtrUsage.h"
#include "smart_pointers/MakeSmartPtr.h"
#include "smart_pointers/PimplIdiom.h"

// 完美转发
#include "forwarding/PerfectForwarding.h"
#include "forwarding/UniversalReferences.h"
#include "forwarding/OverloadingAlternatives.h"

// Lambda表达式
#include "lambdas/LambdaCaptures.h"
#include "lambdas/InitCapture.h"
#include "lambdas/DecltypeForwarding.h"
#include "lambdas/LambdaVsBind.h"

// 并发编程
#include "concurrency/TaskBasedProgramming.h"
#include "concurrency/ThreadRAII.h"
#include "concurrency/ThreadHandleDestruction.h"
#include "concurrency/EventNotification.h"
#include "concurrency/AtomicVsVolatile.h"
#include "concurrency/PassByValue.h"
#include "concurrency/Emplacement.h"

/**
 * @brief Item运行器映射表
 * 将命令行参数映射到对应的Demo运行器
 */
std::map<std::string, std::function<void()>> createItemRunners() {
    return {
        // 类型推导
        {"template", []() { TemplateTypeDeduction::Demo().run(); }},
        {"auto", []() { AutoTypeDeduction::Demo().run(); }},
        {"decltype", []() { DecltypeUsage::Demo().run(); }},
        
        // 现代特性
        {"prefer-auto", []() { PreferAuto::Demo().run(); }},
        {"brace-init", []() { BraceInitialization::Demo().run(); }},
        {"nullptr", []() { PreferNullptr::Demo().run(); }},
        {"scoped-enum", []() { ScopedEnums::Demo().run(); }},
        {"noexcept", []() { NoexceptFunctions::Demo().run(); }},
        {"constexpr", []() { ConstexprUsage::Demo().run(); }},
        {"thread-safe", []() { ThreadSafeConst::Demo().run(); }},
        {"special-member", []() { SpecialMemberFunctions::Demo().run(); }},
        
        // 智能指针
        {"unique-ptr", []() { UniquePtrUsage::Demo().run(); }},
        {"shared-ptr", []() { SharedPtrUsage::Demo().run(); }},
        {"weak-ptr", []() { WeakPtrUsage::Demo().run(); }},
        {"make-smart", []() { MakeSmartPtr::Demo().run(); }},
        {"pimpl", []() { PimplIdiom::Demo().run(); }},
        
        // 完美转发
        {"perfect-forward", []() { PerfectForwarding::Demo().run(); }},
        {"universal-ref", []() { UniversalReferences::Demo().run(); }},
        {"overloading", []() { OverloadingAlternatives::Demo().run(); }},
        
        // Lambda表达式
        {"lambda-capture", []() { LambdaCaptures::Demo().run(); }},
        {"init-capture", []() { InitCapture::Demo().run(); }},
        {"decltype-forward", []() { DecltypeForwarding::Demo().run(); }},
        {"lambda-bind", []() { LambdaVsBind::Demo().run(); }},
        
        // 并发编程
        {"task-based", []() { TaskBasedProgramming::Demo().run(); }},
        {"thread-raii", []() { ThreadRAII::Demo().run(); }},
        {"thread-handle", []() { ThreadHandleDestruction::Demo().run(); }},
        {"event-notification", []() { EventNotification::DemoPromise().run(); }},
        {"atomic", []() { AtomicVsVolatile::Demo().run(); }},
        {"pass-by-value", []() { PassByValue::Demo().run(); }},
        {"emplace", []() { Emplacement::Demo().run(); }},
    };
}

/**
 * @brief 打印所有可用的Item
 */
void printAvailableItems() {
    std::cout << "========================================\n";
    std::cout << "  Effective Modern C++ - 可用Item列表\n";
    std::cout << "========================================\n\n";
    
    std::cout << "【类型推导】\n";
    std::cout << "  template          - 模板类型推导\n";
    std::cout << "  auto              - auto类型推导\n";
    std::cout << "  decltype          - decltype的使用\n\n";
    
    std::cout << "【现代特性】\n";
    std::cout << "  prefer-auto       - 优先使用auto\n";
    std::cout << "  brace-init        - 大括号初始化\n";
    std::cout << "  nullptr           - 优先使用nullptr\n";
    std::cout << "  scoped-enum       - 限域枚举\n";
    std::cout << "  noexcept          - noexcept函数\n";
    std::cout << "  constexpr         - constexpr的使用\n";
    std::cout << "  thread-safe       - 线程安全的const\n";
    std::cout << "  special-member    - 特殊成员函数\n\n";
    
    std::cout << "【智能指针】\n";
    std::cout << "  unique-ptr        - std::unique_ptr\n";
    std::cout << "  shared-ptr        - std::shared_ptr\n";
    std::cout << "  weak-ptr          - std::weak_ptr\n";
    std::cout << "  make-smart        - make_unique/make_shared\n";
    std::cout << "  pimpl             - Pimpl惯用法\n\n";
    
    std::cout << "【完美转发】\n";
    std::cout << "  perfect-forward   - 完美转发\n";
    std::cout << "  universal-ref     - 通用引用\n";
    std::cout << "  overloading       - 重载替代方案\n\n";
    
    std::cout << "【Lambda表达式】\n";
    std::cout << "  lambda-capture    - Lambda捕获\n";
    std::cout << "  init-capture      - 初始化捕获\n";
    std::cout << "  decltype-forward  - decltype与转发\n";
    std::cout << "  lambda-bind       - Lambda vs std::bind\n\n";
    
    std::cout << "【并发编程】\n";
    std::cout << "  task-based        - 基于任务的编程\n";
    std::cout << "  thread-raii       - 线程RAII\n";
    std::cout << "  thread-handle     - 线程句柄析构\n";
    std::cout << "  event-notification- 事件通知\n";
    std::cout << "  atomic            - atomic vs volatile\n";
    std::cout << "  pass-by-value     - 按值传递\n";
    std::cout << "  emplace           - 置入而非插入\n\n";
    
    std::cout << "========================================\n";
    std::cout << "使用方法:\n";
    std::cout << "  EffectiveModernCPP.exe [item-name]\n";
    std::cout << "  EffectiveModernCPP.exe --list\n";
    std::cout << "  EffectiveModernCPP.exe --all\n";
    std::cout << "========================================\n";
}

/**
 * @brief 运行所有Item
 */
void runAllItems() {
    auto runners = createItemRunners();
    std::cout << "\n========== 运行所有Item ==========\n\n";
    
    int count = 0;
    for (const auto& [name, runner] : runners) {
        std::cout << "\n[" << ++count << "/" << runners.size() << "] 运行: " << name << "\n";
        std::cout << "----------------------------------------\n";
        try {
            runner();
        } catch (const std::exception& e) {
            std::cerr << "错误: " << e.what() << "\n";
        }
        std::cout << "\n";
    }
    
    std::cout << "\n========== 完成 ==========\n";
}

/**
 * @brief 打印使用说明
 */
void printUsage(const char* programName) {
    std::cout << "用法: " << programName << " [选项]\n\n";
    std::cout << "选项:\n";
    std::cout << "  [无参数]          运行默认Item (emplace)\n";
    std::cout << "  --list, -l        列出所有可用的Item\n";
    std::cout << "  --all, -a         运行所有Item\n";
    std::cout << "  --help, -h        显示此帮助信息\n";
    std::cout << "  [item-name]       运行指定的Item\n\n";
    std::cout << "示例:\n";
    std::cout << "  " << programName << " template\n";
    std::cout << "  " << programName << " --list\n";
    std::cout << "  " << programName << " --all\n";
}

/**
 * @brief 主函数
 * @param argc 参数个数
 * @param argv 参数数组
 * @return 程序退出码
 */
int main(int argc, char* argv[])
{
    auto runners = createItemRunners();
    
    // 无参数：运行默认Item
    if (argc == 1) {
        std::cout << "运行默认Item: emplace (Item42)\n";
        std::cout << "使用 --list 查看所有可用的Item\n\n";
        Emplacement::Demo().run();
        return 0;
    }
    
    std::string arg = argv[1];
    
    // 帮助信息
    if (arg == "--help" || arg == "-h") {
        printUsage(argv[0]);
        return 0;
    }
    
    // 列出所有Item
    if (arg == "--list" || arg == "-l") {
        printAvailableItems();
        return 0;
    }
    
    // 运行所有Item
    if (arg == "--all" || arg == "-a") {
        runAllItems();
        return 0;
    }
    
    // 运行指定的Item
    auto it = runners.find(arg);
    if (it != runners.end()) {
        std::cout << "运行Item: " << arg << "\n\n";
        try {
            it->second();
        } catch (const std::exception& e) {
            std::cerr << "错误: " << e.what() << "\n";
            return 1;
        }
    } else {
        std::cerr << "错误: 未找到Item '" << arg << "'\n";
        std::cerr << "使用 --list 查看所有可用的Item\n";
        return 1;
    }
    
    return 0;
}