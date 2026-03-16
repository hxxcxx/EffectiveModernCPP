# Effective Modern C++ - 示例代码集合

《Effective Modern C++》书籍的示例代码集合，包含42个条款的演示代码。项目已重构为现代化的CMake构建系统，按功能分类组织代码结构。

## 📋 项目概述

本项目是《Effective Modern C++》一书的配套示例代码，涵盖了现代C++的核心概念和最佳实践：

- ✅ **类型推导**: 模板类型推导、auto类型推导、decltype
- ✅ **现代特性**: auto、nullptr、enum class、noexcept、constexpr
- ✅ **智能指针**: unique_ptr、shared_ptr、weak_ptr
- ✅ **完美转发**: 移动语义、完美转发、通用引用
- ✅ **Lambda表达式**: 捕获模式、初始化捕获
- ✅ **并发编程**: 任务编程、线程安全、原子操作

## 🎯 项目特点

- 🏗️ **现代化构建**: 使用CMake构建系统，支持跨平台编译
- 📁 **清晰组织**: 按功能分类，易于查找和学习
- 📝 **描述性命名**: 文件名和命名空间名称清晰易懂
- 📚 **完善文档**: 详细的构建说明和代码分析
- 🔧 **易于扩展**: 结构清晰，便于添加新的示例

## 🚀 快速开始

### 前提条件

- CMake 3.15或更高版本
- Visual Studio 2022（或其他C++17兼容编译器）
- Boost库 1.55.0或更高版本（可选）

### Windows构建（Visual Studio 2022）

```powershell
# 克隆或下载项目
cd F:\code2028\EffectiveModernCPP

# 创建构建目录
mkdir build
cd build

# 生成Visual Studio项目文件
cmake -G "Visual Studio 17 2022" -A x64 ..

# 构建项目（Release配置）
cmake --build . --config Release

# 运行程序
.\bin\Release\EffectiveModernCPP.exe
```

### Linux/macOS构建

```bash
# 创建构建目录
mkdir build
cd build

# 配置项目
cmake ..

# 构建
make -j$(nproc)

# 运行
./EffectiveModernCPP
```

## 📁 项目结构

```
EffectiveModernCPP/
├── CMakeLists.txt              # CMake构建配置
├── main.cpp                    # 主程序入口
├── README.md                   # 本文档
├── BUILD.md                    # 详细构建说明
├── ITEMS_ANALYSIS.md           # Item分析文档
│
├── type_deduction/             # 类型推导相关
│   ├── TemplateTypeDeduction.h      # Item1: 模板类型推导
│   ├── AutoTypeDeduction.h          # Item2: auto类型推导
│   └── DecltypeUsage.h              # Item3: decltype的使用
│
├── modern_features/           # 现代C++特性
│   ├── PreferAuto.h                # Item5: 优先使用auto
│   ├── BraceInitialization.h       # Item7: 大括号初始化
│   ├── PreferNullptr.h             # Item8: 优先使用nullptr
│   ├── ScopedEnums.h               # Item10: 限域枚举
│   ├── NoexceptFunctions.h         # Item14: noexcept函数
│   ├── ConstexprUsage.h            # Item15: constexpr的使用
│   ├── ThreadSafeConst.h           # Item16: 线程安全的const成员函数
│   └── SpecialMemberFunctions.h    # Item17: 特殊成员函数
│
├── smart_pointers/            # 智能指针
│   ├── UniquePtrUsage.h            # Item18: std::unique_ptr的使用
│   ├── SharedPtrUsage.h            # Item19: std::shared_ptr的使用
│   ├── WeakPtrUsage.h              # Item20: std::weak_ptr的使用
│   ├── MakeSmartPtr.h              # Item21: 使用make_unique和make_shared
│   ├── PimplIdiom.h                # Item22: Pimpl惯用法
│   └── PimplIdiom.cxx              # Item22实现文件
│
├── forwarding/                # 完美转发
│   ├── PerfectForwarding.h         # Item23: 完美转发
│   ├── UniversalReferences.h       # Item24: 通用引用
│   └── OverloadingAlternatives.h   # Item27: 重载通用引用的替代方案
│
├── lambdas/                   # Lambda表达式
│   ├── LambdaCaptures.h            # Item31: Lambda捕获
│   ├── InitCapture.h               # Item32: 初始化捕获
│   ├── DecltypeForwarding.h        # Item33: decltype与转发
│   └── LambdaVsBind.h              # Item34: Lambda vs std::bind
│
├── concurrency/               # 并发编程
│   ├── TaskBasedProgramming.h     # Item35: 基于任务的编程
│   ├── ThreadRAII.h                # Item37: 线程RAII
│   ├── ThreadHandleDestruction.h   # Item38: 线程句柄析构行为
│   ├── EventNotification.h         # Item39: 事件通知
│   ├── AtomicVsVolatile.h          # Item40: atomic vs volatile
│   ├── PassByValue.h               # Item41: 按值传递
│   └── Emplacement.h               # Item42: 置入而非插入
│
├── utils/                     # 工具类
│   └── type.h                     # 类型打印工具
│
└── build/                     # 构建目录（自动生成）
    └── bin/
        └── Release/
            └── EffectiveModernCPP.exe
```

## 📂 文件夹分类说明

### 1. type_deduction（类型推导）
包含与C++类型推导相关的示例：
- **TemplateTypeDeduction**: 演示模板参数类型推导规则（值传递、引用传递、万能引用、数组/函数退化）
- **AutoTypeDeduction**: 演示auto的类型推导规则（顶层const去除、初始化列表推导）
- **DecltypeUsage**: 演示decltype的类型推导和返回类型推导（decltype((x)) vs decltype(x)）

### 2. modern_features（现代特性）
包含现代C++语言特性的示例：
- **PreferAuto**: 优先使用auto而非显式类型（简化代码、避免类型不匹配）
- **BraceInitialization**: 大括号初始化vs圆括号初始化（防止窄化转换、避免most vexing parse）
- **PreferNullptr**: 优先使用nullptr而非0或NULL（类型安全、模板优势）
- **ScopedEnums**: 使用enum class而非传统enum（作用域限定、类型安全）
- **NoexceptFunctions**: 使用noexcept修饰函数（性能优化、移动构造）
- **ConstexprUsage**: 使用constexpr进行编译期计算（编译期常量、constexpr函数）
- **ThreadSafeConst**: 保证const成员函数的线程安全（std::atomic、std::mutex、mutable）
- **SpecialMemberFunctions**: 特殊成员函数的生成规则（拷贝/移动构造、=default/=delete）

### 3. smart_pointers（智能指针）
包含C++智能指针的示例：
- **UniquePtrUsage**: std::unique_ptr的使用（独占所有权、自定义删除器、多态基类）
- **SharedPtrUsage**: std::shared_ptr的使用（共享所有权、引用计数、shared_from_this）
- **WeakPtrUsage**: std::weak_ptr的使用（避免悬空引用、打破循环引用）
- **MakeSmartPtr**: 使用make_unique和make_shared（内存效率、异常安全）
- **PimplIdiom**: Pimpl惯用法（编译防火墙、二进制兼容性、实现隐藏）

### 4. forwarding（完美转发）
包含完美转发和移动语义的示例：
- **PerfectForwarding**: 完美转发的实现（std::forward vs std::move、引用折叠规则）
- **UniversalReferences**: 通用引用的概念（通用引用vs右值引用、类型推导上下文）
- **OverloadingAlternatives**: 避免重载通用引用的方法（标签分发、std::enable_if、SFINAE）

### 5. lambdas（Lambda表达式）
包含Lambda表达式相关的示例：
- **LambdaCaptures**: Lambda的捕获模式（默认捕获问题、捕获this指针、避免悬空引用）
- **InitCapture**: C++14的初始化捕获（init-capture语法、移动捕获）
- **DecltypeForwarding**: decltype在完美转发中的应用（decltype(auto)、auto&&）
- **LambdaVsBind**: Lambda相比std::bind的优势（可读性、编译期检查、性能）

### 6. concurrency（并发编程）
包含并发编程的示例：
- **TaskBasedProgramming**: 基于任务的编程vs基于线程（std::async、future、异常处理）
- **ThreadRAII**: 确保线程的unjoinable状态（RAII包装、析构时join/detach）
- **ThreadHandleDestruction**: 线程句柄的析构行为（future析构阻塞、packaged_task）
- **EventNotification**: 线程间的事件通知（promise/future、condition_variable、atomic标志）
- **AtomicVsVolatile**: std::atomic vs volatile的正确使用（atomic用于并发、volatile用于特殊内存）
- **PassByValue**: 何时考虑按值传递参数（移动语义影响、性能考虑）
- **Emplacement**: 使用emplace而非insert（就地构造、性能优势）

### 7. utils（工具类）
包含项目使用的工具类：
- **type.h**: 类型打印工具（支持Boost和备用实现）

## 🔄 命名空间映射

所有Item类都已重命名为更具描述性的命名空间：

| 原命名空间 | 新命名空间 | 文件位置 |
|-----------|-----------|---------|
| Item1 | TemplateTypeDeduction | type_deduction/ |
| Item2 | AutoTypeDeduction | type_deduction/ |
| Item3 | DecltypeUsage | type_deduction/ |
| Item5 | PreferAuto | modern_features/ |
| Item7 | BraceInitialization | modern_features/ |
| Item8 | PreferNullptr | modern_features/ |
| Item10 | ScopedEnums | modern_features/ |
| Item14 | NoexceptFunctions | modern_features/ |
| Item15 | ConstexprUsage | modern_features/ |
| Item16 | ThreadSafeConst | modern_features/ |
| Item17 | SpecialMemberFunctions | modern_features/ |
| Item18 | UniquePtrUsage | smart_pointers/ |
| Item19 | SharedPtrUsage | smart_pointers/ |
| Item20 | WeakPtrUsage | smart_pointers/ |
| Item21 | MakeSmartPtr | smart_pointers/ |
| Item22 | PimplIdiom | smart_pointers/ |
| Item23 | PerfectForwarding | forwarding/ |
| Item24 | UniversalReferences | forwarding/ |
| Item27 | OverloadingAlternatives | forwarding/ |
| Item31 | LambdaCaptures | lambdas/ |
| Item32 | InitCapture | lambdas/ |
| Item33 | DecltypeForwarding | lambdas/ |
| Item34 | LambdaVsBind | lambdas/ |
| Item35 | TaskBasedProgramming | concurrency/ |
| Item37 | ThreadRAII | concurrency/ |
| Item38 | ThreadHandleDestruction | concurrency/ |
| Item39 | EventNotification | concurrency/ |
| Item40 | AtomicVsVolatile | concurrency/ |
| Item41 | PassByValue | concurrency/ |
| Item42 | Emplacement | concurrency/ |

## 📝 使用示例

### 运行特定的Item

修改`main.cpp`中的调用：

```cpp
int main()
{
    // 运行类型推导示例
    TemplateTypeDeduction::Demo().run();
    
    // 或运行auto类型推导示例
    AutoTypeDeduction::Demo().run();
    
    // 或运行智能指针示例
    UniquePtrUsage::Demo().run();
}
```

### 添加新的Item

1. 在对应的文件夹中创建新的头文件
2. 使用描述性的命名空间名称
3. 在`main.cpp`中添加include
4. 在`CMakeLists.txt`中添加文件路径

## 📖 学习路径

建议按以下顺序学习：

1. **类型推导** (type_deduction) - 理解C++的类型系统
2. **现代特性** (modern_features) - 掌握现代C++特性
3. **智能指针** (smart_pointers) - 学习资源管理
4. **完美转发** (forwarding) - 理解移动语义
5. **Lambda表达式** (lambdas) - 掌握函数式编程
6. **并发编程** (concurrency) - 学习多线程编程

## 🔧 维护指南

### 添加新文件时
1. 确定文件所属的类别
2. 在对应文件夹创建文件
3. 使用描述性的命名空间
4. 更新CMakeLists.txt
5. 更新main.cpp（如需要）

### 重构规则
1. 保持文件夹结构的一致性
2. 使用描述性的命名
3. 确保include路径正确
4. 更新相关文档

## 📚 相关文档

- **BUILD.md**: 详细的构建说明
- **ITEMS_ANALYSIS.md**: 每个Item的详细分析
- **REFACTORING_SUMMARY.md**: 重构总结

## 🎯 设计原则

1. **按功能分类**: 文件按功能主题组织到不同文件夹
2. **描述性命名**: 使用描述性的文件名和命名空间名称
3. **清晰的层次**: 文件夹结构清晰，易于导航
4. **易于扩展**: 新的Item可以轻松添加到对应的文件夹
5. **跨平台支持**: 使用CMake构建系统，支持多平台编译

## 📄 许可证

本项目仅用于学习目的。

