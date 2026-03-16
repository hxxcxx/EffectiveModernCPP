# Effective Modern C++ - 构建说明

## 项目概述

本项目是《Effective Modern C++》书籍的示例代码集合，已从Visual Studio项目重构为CMake构建系统，支持跨平台编译。

## 重构内容

### 1. 命名空间重命名
所有Item类已重命名为更具描述性的名称：

| 原命名空间 | 新命名空间 | 说明 |
|-----------|-----------|------|
| Item1 | TemplateTypeDeduction | 模板类型推导 |
| Item2 | AutoTypeDeduction | auto类型推导 |
| Item3 | DecltypeUsage | decltype的使用 |
| Item5 | PreferAuto | 优先使用auto |
| Item7 | BraceInitialization | 大括号初始化 |
| Item8 | PreferNullptr | 优先使用nullptr |
| Item10 | ScopedEnums | 限域枚举 |
| Item14 | NoexceptFunctions | noexcept函数 |
| Item15 | ConstexprUsage | constexpr的使用 |
| Item16 | ThreadSafeConst | 线程安全的const成员函数 |
| Item17 | SpecialMemberFunctions | 特殊成员函数 |
| Item18 | UniquePtrUsage | std::unique_ptr的使用 |
| Item19 | SharedPtrUsage | std::shared_ptr的使用 |
| Item20 | WeakPtrUsage | std::weak_ptr的使用 |
| Item21 | MakeSmartPtr | 使用make_unique和make_shared |
| Item22 | PimplIdiom | Pimpl惯用法 |
| Item23 | PerfectForwarding | 完美转发 |
| Item24 | UniversalReferences | 通用引用 |
| Item27 | OverloadingAlternatives | 重载通用引用的替代方案 |
| Item31 | LambdaCaptures | Lambda捕获 |
| Item32 | InitCapture | 初始化捕获 |
| Item33 | DecltypeForwarding | decltype与转发 |
| Item34 | LambdaVsBind | Lambda vs std::bind |
| Item35 | TaskBasedProgramming | 基于任务的编程 |
| Item37 | ThreadRAII | 线程RAII |
| Item38 | ThreadHandleDestruction | 线程句柄析构行为 |
| Item39 | EventNotification | 事件通知 |
| Item40 | AtomicVsVolatile | atomic vs volatile |
| Item41 | PassByValue | 按值传递 |
| Item42 | Emplacement | 置入而非插入 |

### 2. CMake构建系统
- 创建了CMakeLists.txt配置文件
- 支持Visual Studio 2022
- 支持C++17标准
- 自动检测Boost库（可选）
- 提供备用实现，无需Boost也能编译

## 构建说明

### 前提条件
- CMake 3.15或更高版本
- Visual Studio 2022（或其他C++17兼容编译器）
- Boost库 1.55.0或更高版本（可选）

### Windows构建（Visual Studio 2022）

#### 1. 使用CMake命令行

```powershell
# 创建构建目录
cd F:\code2028\EffectiveModernCPP
mkdir build
cd build

# 生成Visual Studio项目文件
cmake -G "Visual Studio 17 2022" -A x64 ..

# 构建项目（Release配置）
cmake --build . --config Release

# 运行程序
.\bin\Release\EffectiveModernCPP.exe
```

#### 2. 使用Visual Studio IDE

1. 打开Visual Studio 2022
2. 选择"打开本地文件夹"
3. 选择`F:\code2028\EffectiveModernCPP`目录
4. Visual Studio会自动识别CMakeLists.txt并配置项目
5. 选择"生成" -> "全部生成"
6. 按F5运行程序

### Linux/macOS构建

```bash
# 创建构建目录
cd /path/to/EffectiveModernCPP
mkdir build
cd build

# 配置项目
cmake ..

# 构建
make -j$(nproc)

# 运行
./EffectiveModernCPP
```

## 依赖项说明

### Boost库（可选）
项目支持两种模式：

1. **使用Boost库**（推荐）
   - 提供更准确的类型信息显示
   - 需要安装Boost库
   - CMake会自动检测并使用

2. **不使用Boost库**
   - 使用编译器内置的类型信息
   - 无需额外安装
   - 功能完全正常

如果安装了Boost，CMake会自动检测并使用。如果没有安装，项目会使用备用实现。

### 安装Boost（可选）

#### Windows
```powershell
# 使用vcpkg
vcpkg install boost:x64-windows

# 或手动下载并配置
# 设置环境变量 BOOST_ROOT 指向Boost安装目录
```

#### Linux
```bash
# Ubuntu/Debian
sudo apt-get install libboost-all-dev

# Fedora
sudo dnf install boost-devel

# macOS
brew install boost
```

## 项目结构

```
EffectiveModernCPP/
├── CMakeLists.txt              # CMake构建配置
├── main.cpp                    # 主程序入口
├── README.md                   # 项目说明（包含项目结构和核心概念）
├── BUILD.md                    # 本文档
├── REFACTORING_SUMMARY.md      # 重构总结
│
├── type_deduction/             # 类型推导相关
├── modern_features/           # 现代C++特性
├── smart_pointers/            # 智能指针
├── forwarding/                # 完美转发
├── lambdas/                   # Lambda表达式
├── concurrency/               # 并发编程
├── utils/                     # 工具类
│
└── build/                     # 构建目录（自动生成）
    └── bin/
        └── Release/
            └── EffectiveModernCPP.exe
```

详细的项目结构说明和核心概念请参阅 [README.md](README.md)

## 运行不同的Item

要运行特定的Item，修改`main.cpp`中的调用：

```cpp
int main()
{
    // 运行Item42（置入而非插入）
    Emplacement::Demo().run();
    
    // 或运行其他Item，例如：
    // TemplateTypeDeduction::Demo().run();      // Item1: 模板类型推导
    // AutoTypeDeduction::Demo().run();          // Item2: auto类型推导
    // ConstexprUsage::Demo().run();             // Item15: constexpr的使用
    // UniquePtrUsage::Demo().run();             // Item18: std::unique_ptr的使用
    // PerfectForwarding::Demo().run();          // Item23: 完美转发
    // LambdaCaptures::Demo().run();             // Item31: Lambda捕获
    // TaskBasedProgramming::Demo().run();       // Item35: 基于任务的编程
}
```

所有可用的命名空间请参阅 [README.md](README.md) 中的命名空间映射表。

## 编译选项

项目使用以下编译选项：

### MSVC（Visual Studio）
- `/W4` - 高级警告级别
- `/permissive-` - 严格标准符合性
- `/Zc:__cplusplus` - 正确的__cplusplus宏值
- `/MP` - 多核编译

### GCC/Clang
- `-Wall` - 所有警告
- `-Wextra` - 额外警告
- `-Wpedantic` - 严格标准符合性

## 故障排除

### 问题：找不到Boost库
**解决方案**：
1. 安装Boost库
2. 或让项目使用备用实现（会自动回退）

### 问题：CMake版本过低
**解决方案**：
- 升级CMake到3.15或更高版本

### 问题：编译器不支持C++17
**解决方案**：
- 升级到Visual Studio 2017 15.3或更高版本
- 或GCC 7.0或更高版本
- 或Clang 5.0或更高版本

## 贡献

欢迎提交问题和改进建议！

## 许可证

本项目仅用于学习目的。
