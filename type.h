#pragma once
#include <boost/type_index.hpp>
#include <string_view>
#include <string>
#if 0
#if defined(__clang__) || defined(__GNUC__)
    #define FUNCTION_SIGNATURE __PRETTY_FUNCTION__
#elif defined(_MSC_VER)
    #define FUNCTION_SIGNATURE __FUNCSIG__
#endif


template<typename T>
std::string_view printType() {
    std::string_view sig = FUNCTION_SIGNATURE;

    // 查找 "T = " 的位置
    auto start = sig.find("T = ");
    if (start == std::string_view::npos)
        return "unknown";

    start += 4;  // 跳过 "T = "
    
    // 在后续第一个 ']' 或 ';' 或 '>' 前截断
    auto end = sig.find_first_of("]>;", start);
    return sig.substr(start, end - start);
}
#else
template<typename T>
std::string printType() {
    return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}
#endif
