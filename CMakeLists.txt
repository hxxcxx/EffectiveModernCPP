cmake_minimum_required(VERSION 3.15)

# 项目信息
project(EffectiveModernCPP
    VERSION 1.0.0
    DESCRIPTION "Effective Modern C++ - 示例代码集合"
    LANGUAGES CXX
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项
if(MSVC)
    # MSVC编译选项
    add_compile_options(/W4 /permissive-)
    # 启用C++14/17特性
    add_compile_options(/Zc:__cplusplus)
    # 设置为使用多核编译
    add_compile_options(/MP)
else()
    # GCC/Clang编译选项
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 查找依赖项
# 尝试查找Boost，但不是必需的
find_package(Boost 1.55.0 COMPONENTS system)

# 如果找到了Boost，使用它
if(Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    message(STATUS "Boost include dirs: ${Boost_INCLUDE_DIRS}")
    add_definitions(-DUSE_BOOST)
    # 包含目录
    include_directories(${Boost_INCLUDE_DIRS})
    # 链接库
    set(BOOST_LIBRARIES Boost::system)
else()
    message(WARNING "Boost not found. Using fallback implementation for type printing.")
    # 不需要链接Boost库
    set(BOOST_LIBRARIES "")
endif()

# 源文件列表
set(HEADER_FILES
    # 类型推导
    type_deduction/TemplateTypeDeduction.h
    type_deduction/AutoTypeDeduction.h
    type_deduction/DecltypeUsage.h
    
    # 现代特性
    modern_features/PreferAuto.h
    modern_features/BraceInitialization.h
    modern_features/PreferNullptr.h
    modern_features/ScopedEnums.h
    modern_features/NoexceptFunctions.h
    modern_features/ConstexprUsage.h
    modern_features/ThreadSafeConst.h
    modern_features/SpecialMemberFunctions.h
    
    # 智能指针
    smart_pointers/UniquePtrUsage.h
    smart_pointers/SharedPtrUsage.h
    smart_pointers/WeakPtrUsage.h
    smart_pointers/MakeSmartPtr.h
    smart_pointers/PimplIdiom.h
    smart_pointers/PimplIdiom.cxx
    
    # 完美转发
    forwarding/PerfectForwarding.h
    forwarding/UniversalReferences.h
    forwarding/OverloadingAlternatives.h
    
    # Lambda表达式
    lambdas/LambdaCaptures.h
    lambdas/InitCapture.h
    lambdas/DecltypeForwarding.h
    lambdas/LambdaVsBind.h
    
    # 并发编程
    concurrency/TaskBasedProgramming.h
    concurrency/ThreadRAII.h
    concurrency/ThreadHandleDestruction.h
    concurrency/EventNotification.h
    concurrency/AtomicVsVolatile.h
    concurrency/PassByValue.h
    concurrency/Emplacement.h
    
    # 工具类
    utils/type.h
)

# 主程序源文件
set(MAIN_SOURCE main.cpp)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SOURCE} ${HEADER_FILES})

# 链接库
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${BOOST_LIBRARIES}
)

# 设置输出目录
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# 安装规则
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

# 打印配置信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Boost Version: ${Boost_VERSION}")
message(STATUS "Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
