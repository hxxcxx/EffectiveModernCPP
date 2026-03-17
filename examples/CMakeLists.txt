# 示例程序CMake配置

# 示例程序列表
set(EXAMPLES
    basic_type_deduction
    smart_pointer_basics
    lambda_basics
)

# 为每个示例创建可执行文件
foreach(example ${EXAMPLES})
    add_executable(${example} ${example}.cpp)
    
    # 设置输出目录
    set_target_properties(${example} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples"
    )
    
    # 如果在主项目中，链接utils目录
    if(EXISTS "${CMAKE_SOURCE_DIR}/utils/type.h")
        target_include_directories(${example} PRIVATE ${CMAKE_SOURCE_DIR})
    endif()
endforeach()

# 打印信息
message(STATUS "Examples: ${EXAMPLES}")
