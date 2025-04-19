#include <iostream>
#include <type_traits>
#include <string>
#include <utility>
//Item 27: Familiarize yourself with alternatives to overloading on universal references
namespace Item27 {

    class TagDispatch
    {
    public:
        void logImpl(int val, std::true_type) {
            std::cout << "[int] value: " << val << "\n";
        }

        template<typename T>
        void logImpl(T&& val, std::false_type) {
            std::cout << "[other] value: " << val << "\n";
        }

        template<typename T>
        void logValue(T&& val) {
            // 调用时根据类型派发
            logImpl(std::forward<T>(val), std::is_same<std::decay_t<T>, int>{});
        }

    };

    class EnableIf
    {
    public:
        template<typename T,
            std::enable_if_t<std::is_same<std::decay_t<T>, int>::value, int> = 0>
        void logValue(T&& val) {
            std::cout << "[int] value: " << val << "\n";
        }

        template<typename T,
            std::enable_if_t<!std::is_same<std::decay_t<T>, int>::value, int> = 0>
        void logValue(T&& val) {
            std::cout << "[other] value: " << val << "\n";
        }

    };

    class Person {
    public:
        // 通用构造函数模板，排除 Person 类型和整型
        template<typename T, typename = std::enable_if_t<
                                        !std::is_base_of<Person, std::decay_t<T>>::value &&
                                        !std::is_integral<std::remove_reference_t<T>>::value
                                        >>
        explicit Person(T&& n)
            : name(std::forward<T>(n)) {
            std::cout << "Person(T&&) constructor: name = " << name << '\n';
        }

        // 整型索引构造函数
        explicit Person(int idx)
            : name(nameFromIdx(idx)) {
            std::cout << "Person(int) constructor: name = " << name << '\n';
        }

        // 拷贝构造
        Person(const Person& p)
            : name(p.name) {
            std::cout << "Person copy constructor\n";
        }

        // 移动构造
        Person(Person&& p) noexcept
            : name(std::move(p.name)) {
            std::cout << "Person move constructor\n";
        }

        const std::string& getName() const { return name; }

    protected:
        std::string name;

    private:
        static std::string nameFromIdx(int idx) {
            return "Person#" + std::to_string(idx);
        }
    };

    // 派生类 Employee，继承 Person
    class Employee : public Person {
    public:
        using Person::Person;  // 继承构造函数（C++11 起支持）

        Employee(const Employee& e)
            : Person(e), position("Copied") {
            std::cout << "Employee copy constructor\n";
        }

        Employee(Employee&& e) noexcept
            : Person(std::move(e)), position("Moved") {
            std::cout << "Employee move constructor\n";
        }

    private:
        std::string position = "Default";
    };

    class Demo {
    public:

        void testEnableIf() {
            std::cout << "------ Construct with string ------\n";
            Person p1("Alice");  // 调用通用构造
            Employee e1("Bob");  // 派生类构造

            std::cout << "\n------ Construct with int ------\n";
            Person p2(7);        // 调用整型构造
            Employee e2(42);     // 也调用整型构造（继承）

            std::cout << "\n------ Copy constructor ------\n";
            Person p3 = p1;
            Employee e3 = e1;

            std::cout << "\n------ Move constructor ------\n";
            Person p4 = std::move(p2);
            Employee e4 = std::move(e2);
        }
        void run() {
            int a = 42;
            std::string s = "hello";
            TagDispatch tagDispatch;
            tagDispatch.logValue(a);              // [int] value: 42
            tagDispatch.logValue(3.14);           // [other] value: 3.14
            tagDispatch.logValue(s);              // [other] value: hello

            EnableIf enableIf;
            int x = 7;
            enableIf.logValue(x);           // [int]
            enableIf.logValue("test");      // [other]

            testEnableIf();
        }
    };
}
//通用引用和重载的组合替代方案包括使用不同的函数名，通过lvalue - reference - to - const传递形参，按值传递形参，使用tag dispatch。
//通过std::enable_if约束模板，允许组合通用引用和重载使用，但它也控制了编译器在哪种条件下才使用通用引用重载。
//通用引用参数通常具有高效率的优势，但是可用性就值得斟酌。
//Item 28: Understand reference collapsing
namespace Item28 {
    //禁止你声明引用的引用，但是编译器会在特定的上下文中产生这些，模板实例化就是其中一种情况。当编译器生成引用的引用时，引用折叠指导下一步发生什么。
}
//Item29 Assume that move operations are not present, not cheap, and not used
namespace Item29 {
    /*没有移动操作：要移动的对象没有提供移动操作，所以移动的写法也会变成复制操作。
    移动不会更快：要移动的对象提供的移动操作并不比复制速度更快。
    移动不可用：进行移动的上下文要求移动操作不会抛出异常，但是该操作没有被声明为noexcept。
    假定移动操作不存在，成本高，未被使用。
    在已知的类型或者支持移动语义的代码中，就不需要上面的假设。*/
}
//Item 30: Familiarize yourself with perfect forwarding failure cases
namespace Item30 {
    /*当模板类型推导失败或者推导出错误类型，完美转发会失败。
    导致完美转发失败的实参种类有花括号初始化，作为空指针的0或者NULL，
    仅有声明的整型static const数据成员，模板和重载函数的名字，位域。*/
}

