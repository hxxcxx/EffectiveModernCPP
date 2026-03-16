#include <iostream>
#include <string>
#include <utility>
//Item 41: Consider pass by value for copyable parameters that are cheap to move and always copied

namespace PassByValue {
    /*参数 总是要被拷贝 / 移动	 推荐按值（更统一）
    参数类型 移动代价很小	 推荐按值
    参数类型 拷贝 / 移动都很贵	 尽量避免（用 const& 或其他手段）
    参数不一定使用 / 拷贝	 按需引用，避免值传递带来的多余开销*/

    /*对于可拷贝，移动开销低，而且无条件被拷贝的形参，按值传递效率基本与按引用传递效率一致，而且易于实现，还生成更少的目标代码。
    通过构造拷贝形参可能比通过赋值拷贝形参开销大的多。
    按值传递会引起切片问题，所说不适合基类形参类型。*/

    class Logger {
    public:
        Logger(std::string name) : name_(std::move(name)) {
            std::cout << "Constructor for: " << name_ << "\n";
        }

        Logger(const Logger& other) : name_(other.name_) {
            std::cout << "Copy Constructor for: " << name_ << "\n";
        }

        Logger(Logger&& other) noexcept : name_(std::move(other.name_)) {
            std::cout << "Move Constructor for: " << name_ << "\n";
        }

        Logger& operator=(const Logger& other) {
            std::cout << "Copy Assignment for: " << other.name_ << "\n";
            name_ = other.name_;
            return *this;
        }

        Logger& operator=(Logger&& other) noexcept {
            std::cout << "Move Assignment for: " << other.name_ << "\n";
            name_ = std::move(other.name_);
            return *this;
        }

    private:
        std::string name_;
    };
    class Demo {
    public:
        void run() {
            std::cout << "\n[Item41] --- Begin Test ---\n";

            Logger log("DemoLog");

            std::cout << "\nPassing by const reference:\n";
            setLoggerConstRef(log);

            std::cout << "\nPassing by value (copy):\n";
            setLoggerByValue(log);

            std::cout << "\nPassing by value (move):\n";
            setLoggerByValue(Logger("TempLog"));

            std::cout << "[Item41] --- End Test ---\n";
        }

    private:
        // 方式一：传统 const 引用 + 拷贝
        void setLoggerConstRef(const Logger& logger) {
            Logger local = logger; // 总会发生一次拷贝
        }

        // 方式二：现代按值传参
        void setLoggerByValue(Logger logger) {
            Logger local = std::move(logger); // 可能发生拷贝或移动
        }
    };

    class Heavy {
    public:
        Heavy() { std::cout << "[Heavy] Default Constructor\n"; }

        Heavy(const Heavy&) {
            std::cout << "[Heavy] Copy Constructor (heavy)\n";
        }

        Heavy& operator=(const Heavy&) {
            std::cout << "[Heavy] Copy Assignment (light)\n";
            return *this;
        }
    };
    class HeavyDemo {
    public:
       

        void run() {
            testHeavy();
        }

    private:
        void testHeavy() {
            std::cout << "\n=== Testing Heavy ===\n";
            Heavy h;
            std::cout << "\n-> Pass by value:\n";
            setHeavyByValue(h);

            std::cout << "\n-> Pass by const reference + assignment:\n";
            setHeavyByConstRef(h);
        }

        void setHeavyByValue(Heavy h) {
            std::cout << "[setHeavyByValue] Inside function\n";
        }

        void setHeavyByConstRef(const Heavy& h) {
            Heavy local;
            local = h; // only copy assignment
            std::cout << "[setHeavyByConstRef] Inside function\n";
        }

    };

    class Base {
    public:
        virtual ~Base() = default;
        virtual void speak() const {
            std::cout << "[Base] I am Base\n";
        }
    };

    class Derived : public Base {
    public:
        void speak() const override {
            std::cout << "[Derived] I am Derived\n";
        }
    };
    class SlicingDemo {
    public:
        void run() {
            testSlicing();
        }

    private:
        void takeByValue(Base b) {
            std::cout << "[takeByValue] ";
            b.speak();  // slicing occurs
        }

        void takeByRef(const Base& b) {
            std::cout << "[takeByRef] ";
            b.speak();  // polymorphism preserved
        }

        void testSlicing() {
            std::cout << "\n=== Testing Slicing ===\n";
            Derived d;

            std::cout << "\n-> Pass by value:\n";
            takeByValue(d);  // will slice

            std::cout << "\n-> Pass by const reference:\n";
            takeByRef(d);    // correct
        }

    };

}
