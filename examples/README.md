# Effective Modern C++ - 示例程序

本文件夹包含《Effective Modern C++》的独立示例程序，每个示例都专注于演示特定的C++特性。

## 📁 示例列表

### 1. basic_type_deduction.cpp
**主题**: 类型推导基础

演示内容：
- 模板类型推导（值传递、引用传递、万能引用）
- auto类型推导
- decltype类型推导
- 类型推导的规则和陷阱

编译运行：
```bash
g++ -std=c++17 basic_type_deduction.cpp -o basic_type_deduction
./basic_type_deduction
```

### 2. smart_pointer_basics.cpp
**主题**: 智能指针基础

演示内容：
- std::unique_ptr：独占所有权、自定义删除器
- std::shared_ptr：共享所有权、引用计数
- std::weak_ptr：避免循环引用
- 循环引用问题及解决方案

编译运行：
```bash
g++ -std=c++17 smart_pointer_basics.cpp -o smart_pointer_basics
./smart_pointer_basics
```

### 3. lambda_basics.cpp
**主题**: Lambda表达式基础

演示内容：
- Lambda基本语法
- 捕获模式（值捕获、引用捕获、隐式捕获）
- 可变Lambda（mutable）
- 初始化捕获（C++14）
- 泛型Lambda（C++14）
- Lambda与STL算法结合使用
- Lambda作为返回值

编译运行：
```bash
g++ -std=c++17 lambda_basics.cpp -o lambda_basics
./lambda_basics
```

## 🎯 使用建议

### 学习路径

建议按以下顺序学习示例：

1. **basic_type_deduction.cpp** - 理解C++的类型系统
2. **smart_pointer_basics.cpp** - 学习现代资源管理
3. **lambda_basics.cpp** - 掌握函数式编程

### 编译要求

所有示例都需要支持C++17的编译器：

- **GCC**: 7.0或更高版本
- **Clang**: 5.0或更高版本
- **MSVC**: Visual Studio 2017 15.3或更高版本

### 编译选项

推荐使用以下编译选项：

```bash
# GCC/Clang
g++ -std=c++17 -Wall -Wextra -pedantic example.cpp -o example

# MSVC
cl /std:c++17 /W4 example.cpp
```

## 📚 相关资源

- **主项目**: `../` - 完整的Item演示
- **README.md**: `../README.md` - 项目概述
- **BUILD.md**: `../BUILD.md` - 构建说明

## 🔧 扩展示例

你可以基于这些示例创建自己的演示程序：

1. 选择一个主题（如并发编程、完美转发等）
2. 创建一个新的.cpp文件
3. 添加详细的注释和示例代码
4. 在本README中添加说明

## 📝 代码风格

示例程序遵循以下代码风格：

- 使用详细的注释解释每个概念
- 每个函数都有明确的功能说明
- 使用Doxygen风格的注释
- 代码格式清晰，易于阅读

## 🚀 贡献

欢迎添加更多示例程序！请确保：

1. 代码符合C++17标准
2. 添加详细的注释
3. 在本README中添加说明
4. 代码可以独立编译运行

---

**最后更新**: 2026年3月17日  
**C++标准**: C++17
