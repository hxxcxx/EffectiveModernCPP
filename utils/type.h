/**
 * @file type.h
 * @brief 类型打印工具 - 用于在运行时显示C++类型信息
 * 
 * 本工具提供跨平台的类型名称打印功能，支持：
 * - Boost库（提供最准确的类型信息）
 * - MSVC编译器（使用__FUNCSIG__宏）
 * - GCC/Clang编译器（使用__PRETTY_FUNCTION__宏）
 * - 标准库备用方案（使用typeid）
 */

#pragma once
#include <string>
#include <typeinfo>
#include <cctype>

// 检查是否使用Boost
#ifdef USE_BOOST
    #include <boost/type_index.hpp>
#endif

// 定义编译器特定的函数签名宏
#if defined(__clang__) || defined(__GNUC__)
    #define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNCTION_SIGNATURE __FUNCSIG__
#endif

/**
 * @brief 去除类型名称中的空格
 * @param typeStr 原始类型字符串
 * @return 去除空格后的类型字符串
 */
inline std::string removeSpaces(std::string typeStr) {
    std::string result;
    result.reserve(typeStr.length());
    bool inSpace = false;
    
    for (char c : typeStr) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!inSpace) {
                result += ' ';
                inSpace = true;
            }
        } else {
            result += c;
            inSpace = false;
        }
    }
    
    // 去除开头和结尾的空格
    size_t start = result.find_first_not_of(' ');
    if (start != std::string::npos) {
        result = result.substr(start);
    }
    size_t end = result.find_last_not_of(' ');
    if (end != std::string::npos) {
        result = result.substr(0, end + 1);
    }
    
    return result;
}

/**
 * @brief 从MSVC函数签名中提取类型信息
 * @param sig 函数签名字符串
 * @return 提取的类型字符串
 */
inline std::string extractTypeFromMSVC(const std::string& sig) {
    // MSVC格式: "void __cdecl funcName<class T>(void)"
    // 查找 "class " 或 "struct " 后面的类型名
    std::string::size_type pos = sig.find("class ");
    if (pos == std::string::npos) {
        pos = sig.find("struct ");
    }
    
    if (pos != std::string::npos) {
        pos += 6; // 跳过 "class " 或 "struct "
        
        // 查找类型结束位置（遇到 > 或 , 或 ）
        std::string::size_type end = sig.find('>', pos);
        if (end == std::string::npos) {
            end = sig.find(',', pos);
        }
        if (end == std::string::npos) {
            end = sig.find(')', pos);
        }
        
        if (end != std::string::npos) {
            return removeSpaces(sig.substr(pos, end - pos));
        }
    }
    
    // 备用方案：查找 "T =" 格式
    pos = sig.find("T =");
    if (pos != std::string::npos) {
        pos += 3; // 跳过 "T ="
        
        // 查找结束位置
        std::string::size_type end = sig.find_first_of(",)]", pos);
        if (end == std::string::npos) {
            end = sig.length();
        }
        
        return removeSpaces(sig.substr(pos, end - pos));
    }
    
    return "unknown type";
}

/**
 * @brief 从GCC/Clang函数签名中提取类型信息
 * @param sig 函数签名字符串
 * @return 提取的类型字符串
 */
inline std::string extractTypeFromGCC(const std::string& sig) {
    // GCC/Clang格式: "void funcName() [T = Type]"
    // 查找 "T = " 后面的类型名
    std::string::size_type pos = sig.find("T = ");
    if (pos != std::string::npos) {
        pos += 4; // 跳过 "T = "
        
        // 查找结束位置（遇到 ] 或 ; 或 >）
        std::string::size_type end = sig.find_first_of("];>", pos);
        if (end != std::string::npos) {
            return removeSpaces(sig.substr(pos, end - pos));
        }
    }
    
    // 备用方案：查找 "with T = " 格式
    pos = sig.find("with T = ");
    if (pos != std::string::npos) {
        pos += 9; // 跳过 "with T = "
        
        // 查找结束位置
        std::string::size_type end = sig.find_first_of("];,", pos);
        if (end != std::string::npos) {
            return removeSpaces(sig.substr(pos, end - pos));
        }
    }
    
    return "unknown type";
}

/**
 * @brief 打印类型的名称
 * 
 * 这是一个模板函数，用于在运行时获取并打印类型T的名称。
 * 支持多种实现方式：
 * 1. 如果定义了USE_BOOST，使用Boost.TypeIndex（最准确）
 * 2. 否则使用编译器特定的宏（MSVC/GCC/Clang）
 * 3. 最后使用标准库的typeid作为备用方案
 * 
 * @tparam T 要查询的类型
 * @return 类型的字符串表示
 * 
 * @note 保留引用、const和volatile限定符
 * @note 对于函数类型，可能显示不完整
 * 
 * 示例:
 * @code
 * int x = 42;
 * const int& ref = x;
 * std::cout << printType<decltype(x)>() << std::endl;  // "int"
 * std::cout << printType<decltype(ref)>() << std::endl; // "const int&"
 * @endcode
 */
template<typename T>
std::string printType() {
#ifdef USE_BOOST
    // 使用Boost库获取最准确的类型信息
    return boost::typeindex::type_id_with_cvr<T>().pretty_name();
#else
    // 备用实现：使用编译器内置的类型信息
    std::string sig = FUNCTION_SIGNATURE;
    
    #if defined(_MSC_VER)
        // MSVC编译器
        return extractTypeFromMSVC(sig);
    #elif defined(__clang__) || defined(__GNUC__)
        // GCC/Clang编译器
        return extractTypeFromGCC(sig);
    #else
        // 其他编译器：使用标准库的typeid
        // 注意：typeid可能不保留引用、const等限定符
        return std::string("type: ") + typeid(T).name();
    #endif
#endif
}

/**
 * @brief 打印变量的类型名称
 * 
 * 这是一个辅助函数，用于打印变量的类型。
 * 相比printType<T>()，这个函数更直观易用。
 * 
 * @tparam T 变量的类型
 * @param var 要查询类型的变量
 * @return 类型的字符串表示
 * 
 * 示例:
 * @code
 * int x = 42;
 * std::cout << printTypeName(x) << std::endl;  // "int"
 * @endcode
 */
template<typename T>
std::string printTypeName(const T& var) {
    return printType<T>();
}
