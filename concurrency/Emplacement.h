/**
 * @file Emplacement.h
 * @brief 置入而非插入演示（Item 42）
 * 
 * 本文件演示了使用emplace而非insert的优势，这是优化容器性能的重要技巧。
 * 
 * 核心概念：
 * 1. emplace函数在容器中直接构造对象，避免临时对象的创建和销毁
 * 2. insert/push_back函数需要先创建临时对象，再复制/移动到容器中
 * 3. emplace通常比insert更高效，但不会更差
 * 
 * 性能优势的条件：
 * - 值被构造到容器中，而不是直接赋值
 * - 传入的类型与容器的元素类型不一致
 * - 容器不拒绝已经存在的重复值
 * 
 * 注意事项：
 * - emplace可能执行insert拒绝的类型转换
 * - 某些情况下emplace可能不如insert直观
 * - 需要根据具体情况选择使用emplace还是insert
 * 
 * @note 本Item对应《Effective Modern C++》Item 42
 */

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <regex>

namespace Emplacement {
    class EmplaceVsInsertSet {
    public:
        void run() {
            std::cout << "[EmplaceVsInsertSet] begin\n";

            std::set<std::string> s;

            std::string str = "EmplaceTest";

            s.insert(str);                      // 拷贝 str
            s.insert(std::move(str));           // 移动 str
            s.emplace("EmplaceTest");           // 就地构造，无拷贝/移动

            std::cout << "[EmplaceVsInsertSet] end\n";
        }
    };

    class Widget {
    public:
        Widget(int id, const std::string& name) : id(id), name(name) {
            std::cout << "Widget " << name << " constructed.\n";
        }

        // 复制构造函数
        Widget(const Widget& other) : id(other.id), name(other.name) {
            std::cout << "Widget " << name << " copy-constructed.\n";
        }

        // 移动构造函数
        Widget(Widget&& other) noexcept : id(other.id), name(std::move(other.name)) {
            std::cout << "Widget " << name << " move-constructed.\n";
        }

        // 输出内容
        void display() const {
            std::cout << "Widget ID: " << id << ", Name: " << name << "\n";
        }

    private:
        int id;
        std::string name;
    };

    class EmplaceVsInsertVector {
    public:
        void run() {
            std::cout << "[EmplaceVsInsertVector] begin\n";

            std::vector<Widget> v;

            Widget w(1, "One");
            v.push_back(w);                  // 调用复制构造函数
            v.push_back(std::move(w));       // 调用移动构造函数
            v.emplace_back(2, "Two");        // 直接构造，无复制/移动

            std::cout << "[EmplaceVsInsertVector] end\n";
        }
    };

    class EmplaceVsInsertMap {
    public:
        void run() {
            std::cout << "[EmplaceVsInsertMap] begin\n";

            std::unordered_map<int, std::string> m;

            m.insert(std::pair<int, std::string>(1, "One")); // 先构造 pair，然后插入
            m.emplace(2, "Two");                             // 就地构造，无多余构造

            std::cout << "[EmplaceVsInsertMap] end\n";
        }
    };

    class EmplaceVsInsertSmartPtr {
    public:
        void run() {
            std::cout << "[EmplaceVsInsertSmartPtr] begin\n";

            std::vector<std::shared_ptr<Widget>> v;

            // 使用 shared_ptr 创建 Widget 对象
            std::shared_ptr<Widget> w1 = std::make_shared<Widget>(1, "One");
            std::shared_ptr<Widget> w2 = std::make_shared<Widget>(2, "Two");

            // 使用 push_back (拷贝构造)
            v.push_back(w1);  // 共享指针，直接拷贝引用
            std::cout << "After push_back(w1):\n";
            for (const auto& widget : v) {
                widget->display();
            }

            // 使用 move 语义
            v.push_back(std::move(w2));  // 使用移动语义，不会影响原始的 w2
            std::cout << "After push_back(std::move(w2)):\n";
            for (const auto& widget : v) {
                widget->display();
            }

            // 使用 emplace_back (直接构造)
            v.emplace_back(std::make_shared<Widget>(3, "Three"));  // 直接构造，没有拷贝/移动
            std::cout << "After emplace_back(3, 'Three'):\n";
            for (const auto& widget : v) {
                widget->display();
            }

            // 使用 insert 插入元素
            v.insert(v.begin(), std::make_shared<Widget>(4, "Four"));  // 调用共享指针的拷贝构造
            std::cout << "After insert(v.begin(), std::make_shared<Widget>(4, 'Four')):\n";
            for (const auto& widget : v) {
                widget->display();
            }

            std::cout << "[EmplaceVsInsertSmartPtr] end\n";
        }
    };

    class RegexDemo {
    public:
        void run() {
            std::cout << "[RegexDemo] begin\n";

            std::vector<std::regex> regexes;

            try {
                // 使用有效的正则表达式模式添加到容器
                regexes.emplace_back(std::regex(R"(\d{3}-\d{2}-\d{4})"));  // Social Security Number format
                regexes.emplace_back(std::regex(R"([a-zA-Z]+)"));            // Any alphabetic string

                // 使用 nullptr 显示会导致编译错误，因为 std::regex 需要一个有效的正则表达式字符串
                //regexes.emplace_back(nullptr);
                 //regexes.push_back(nullptr); // 这行会导致编译错误
                // 打印容器中的正则表达式数量
                std::cout << "Number of regex patterns: " << regexes.size() << std::endl;

                // 测试正则表达式
                std::string testStr1 = "123-45-6789";
                std::string testStr2 = "abcABC";
                std::string testStr3 = "not_matching_pattern";

                // 使用正则表达式进行匹配
                testRegexMatch(regexes[0], testStr1);
                testRegexMatch(regexes[1], testStr2);
                testRegexMatch(regexes[0], testStr3);  // This should not match

            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }

            std::cout << "[RegexDemo] end\n";
        }

    private:
        void testRegexMatch(const std::regex& reg, const std::string& testStr) {
            if (std::regex_match(testStr, reg)) {
                std::cout << "String \"" << testStr << "\" matches the regex.\n";
            }
            else {
                std::cout << "String \"" << testStr << "\" does NOT match the regex.\n";
            }
        }
    };
    /*插入函数和置入函数的对比。置入函数使用直接初始化，这意味着可能使用explicit的构造函数。插入函数使用拷贝初始化，所以不能用explicit的构造函数。因此：*/
    //当你使用置入函数时，请特别小心确保传递了正确的实参，因为即使是explicit的构造函数也会被编译器考虑，编译器会试图以有效方式解释你的代码。
    class Demo {
    public:
        void run() {
            std::cout << "[Item42] run() begin\n";

            EmplaceVsInsertSet{}.run();
            EmplaceVsInsertVector{}.run();
            EmplaceVsInsertMap{}.run();
            EmplaceVsInsertSmartPtr{}.run();
            RegexDemo{}.run();
            
            std::cout << "[Item42] run() end\n";
        }
    };

}
