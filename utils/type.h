#pragma once
#include <string_view>
#include <string>
#include <typeinfo>

// 检查是否使用Boost
#ifdef USE_BOOST
    #include <boost/type_index.hpp>
#endif

#if defined(__clang__) || defined(__GNUC__)
    #define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNCTION_SIGNATURE __FUNCSIG__
#endif

template<typename T>
std::string printType() {
#ifdef USE_BOOST
    return boost::typeindex::type_id_with_cvr<T>().pretty_name();
#else
    // 备用实现：使用编译器内置的类型信息
    std::string sig = FUNCTION_SIGNATURE;
    
    // 对于MSVC，查找 "T =" 的位置
    #if defined(_MSC_VER)
        auto start = sig.find("T =");
        if (start == std::string::npos)
            return std::string("unknown type: ") + typeid(T).name();
        start += 3;  // 跳过 "T ="
        
        // 查找结束位置
        auto end = sig.find_first_of(",)]", start);
        if (end == std::string::npos)
            end = sig.length();
        
        return sig.substr(start, end - start);
    #else
        // 对于GCC/Clang，使用typeid作为备用
        return std::string("type: ") + typeid(T).name();
    #endif
#endif
}
