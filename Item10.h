#pragma once
#include <iostream>

//Prefer scoped enums to unscoped enums
//在enum后面写一个class就可以将非限域enum转换为限域enum，接下来就是完全不同的故事展开了。现在不存在任何隐式转换可以将限域enum中的枚举名转化为任何其他类型：
namespace Item10 {

    // 传统 unscoped enum
    enum Color { Red, Green, Blue };
    enum Alert { GreenAlert, Yellow, RedAlert };  // 改名避免冲突

    // 推荐的 scoped enum（C++11+）
    enum class ScopedColor { Red, Green, Blue };
    enum class ScopedAlert { Green, Yellow, Red };
    class Demo {
    public:
        /*template<typename E>
        constexpr typename std::underlying_type<E>::type toUType(E enumerator) noexcept
        {
            return static_cast<typename std::underlying_type<E>::type>(enumerator);
        }*/

        //template<typename E>                //C++14
        //constexpr std::underlying_type_t<E> toUType(E enumerator) noexcept
        //{
        //    return static_cast<std::underlying_type_t<E>>(enumerator);
        //}

        //template<typename E>                //C++14
        //constexpr auto toUType(E enumerator) noexcept
        //{
        //    return static_cast<std::underlying_type_t<E>>(enumerator);
        //}

        template<typename E>
        constexpr auto toUType(E enumerator) noexcept {
            static_assert(std::is_enum_v<E>, "toUType requires an enum type!");
            return static_cast<std::underlying_type_t<E>>(enumerator);
        }

        std::vector<std::size_t> primeFactors(std::size_t x) { return  std::vector<std::size_t>{}; }

        void test_tuple() {
            using UserInfo1 =                //类型别名，参见Item9
                std::tuple<std::string,     //名字
                std::string,     //email地址
                std::size_t>;   //声望

            UserInfo1 uInfo;

            auto val = std::get<1>(uInfo);	//获取第一个字段

            enum UserInfoFields { uiName, uiEmail, uiReputation };

            auto val1 = std::get<uiEmail>(uInfo);    //啊，获取用户email字段的值
            //限域enum
            {
                enum class UserFields { Name, Email, Reputation };
                using UserInfo = std::tuple<std::string, std::string, int>;

                UserInfo user{ "Alice", "alice@example.com", 100 };

                // 通过枚举值访问 tuple
                //auto name = std::get<toUType(UserFields::Name)>(user); // 返回 "Alice"
                //auto name = std::get<toUType(UserFields::Name)>(user); // 返回 "Alice"
            }
        };

        void run() {
            Color c = Red;
            if (c < 14.5) auto factors = primeFactors(c);

            ScopedColor s = ScopedColor::Blue;

            //if (s < 14.5) auto factors = primeFactors(c); //限域enum
            if (static_cast<double>(c) < 14.5) {}


            auto white = false;//其实不在一个作用域和COLOR
            Alert a = Yellow;
            std::cout << "[Unscoped] Color: " << c << ", Alert: " << a << "\n";

            // scoped enum：强制作用域限定，更安全
            ScopedColor sc = ScopedColor::Red;
            ScopedAlert sa = ScopedAlert::Yellow;

            // 无法直接输出枚举类，需要显式转换成 int 才行
            std::cout << "[Scoped] Color: " << static_cast<int>(sc)
                << ", Alert: " << static_cast<int>(sa) << "\n";

            // 以下代码无法编译，演示类型安全
            // ScopedColor wrong = 0;               // 错误：不能隐式转 int
            // int n = ScopedColor::Green;         //  错误：不能隐式转 int


            test_tuple();
        }
    };
}
