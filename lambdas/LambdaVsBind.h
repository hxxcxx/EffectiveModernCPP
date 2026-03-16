#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

namespace LambdaVsBind {
    using namespace std;
    using namespace std::chrono;
    void setAlarm(time_point<steady_clock> t) {
        auto now = steady_clock::now();
        auto diff = duration_cast<seconds>(t - now).count();
        std::cout << "[setAlarm] Alarm set to go off in " << diff << " seconds.\n";
    }

    //当setAlarm重载时，会出现一个新问题。编译器无法确定应将两个setAlarm函数中的哪一个传递给std::bind。 它们仅有的是一个函数名称，而这个单一个函数名称是有歧义的。
    //void setAlarm(time_point<steady_clock> t, int i) {
    //    auto now = steady_clock::now();
    //    auto diff = duration_cast<seconds>(t - now).count();
    //    std::cout << "[setAlarm] Alarm set to go off in " << diff << " seconds.\n";
    //}
    //
    //using SetAlarm3ParamType = void(*)(time_point<steady_clock> t);
    //auto boundAlarm = std::bind(static_cast<SetAlarm3ParamType>(setAlarm), steady_clock::now() + 1h);

    class PolyWidget {
    public:
        template<typename T>
        void operator()(const T& param) {
            std::cout << "PolyWidget called with type: " << typeid(T).name()
                << " and value: " << param << "\n";
        }
    };


    class Widget {
    public:
        void print(int rate) const {
            std::cout << "[Widget] compress rate = " << rate << std::endl;
        }
    };

    struct MyType {
        int x = 100;
        friend std::ostream& operator<<(std::ostream& os, const MyType& mt) {
            return os << "MyType(" << mt.x << ")";
        }
    };

    // 普通函数（可与 Widget 配合使用）
    void compress(Widget w, int rate) {
        w.print(rate);
    }

    class Demo {
    public:
        void operatorTest() {
            PolyWidget pw;

            auto boundPW = std::bind(pw, std::placeholders::_1);


            boundPW(1930);              //传int给PolyWidget::operator()
            boundPW(nullptr);           //传nullptr给PolyWidget::operator()
            boundPW("Rosebud"); 		//传字面值给PolyWidget::operator()

            pw(42);                             // int
            pw(3.14);                           // double
            pw(std::string("Hello"));          // std::string
            const char* cstr = "World";
            pw(cstr);                          // const char*



            pw(MyType{});                      // 自定义类型

        }
        void boundAlarmTest() {
            using namespace std::chrono_literals;

            std::cout << "--- std::bind version ---\n";
            auto boundAlarm = std::bind(setAlarm, steady_clock::now() + 1h);
            std::this_thread::sleep_for(2s);  // 模拟晚一点调用
            boundAlarm();  // 实际只剩 3598 秒

            std::cout << "--- lambda version ---\n";
            auto lambdaAlarm = [] {
                setAlarm(steady_clock::now() + 1h);
                };
            std::this_thread::sleep_for(2s);  // 同样延迟
            lambdaAlarm();  // 仍然是完整的 3600 秒


        }
        void bindAndLamdaTest() {
            Widget w;

            // 将 Widget 对象 w 和 compress 绑定，延迟传入 rate 参数
            using namespace std::placeholders;
            auto compressRateB = std::bind(compress, w, _1);

            // 调用绑定函数
            compressRateB(42);  // 输出: [Widget] compress rate = 42
            
            auto compressRateL =                //w是按值捕获，lev是按值传递
                [w](int lev)
                { return compress(w, lev); };


        
        }

        void run() {
            boundAlarmTest();
            bindAndLamdaTest();
            operatorTest();
        }
    };
    //等价于上面的std::bind版本
    struct BoundSetAlarm {
        using TimePoint = std::chrono::steady_clock::time_point;

        // 函数指针（间接调用）
        void (*func)(TimePoint);
        TimePoint tp;

        BoundSetAlarm(void (*f)(TimePoint), TimePoint t)
            : func(f), tp(t) {
        }

        void operator()() const {
            // 间接调用：无法内联
            func(tp);
        }
    };
    //等价于上面的std::bind版本
    struct LambdaSetAlarm {
        using TimePoint = std::chrono::steady_clock::time_point;

        TimePoint tp;

        explicit LambdaSetAlarm(TimePoint t)
            : tp(t) {
        }

        void operator()() const {
            // 直接调用：可以内联
            setAlarm(tp);
        }
    };

    //因此，使用lambda可能会比使用std::bind能生成更快的代码。

}






//与lambda相比，使用std::bind进行编码的代码可读性较低，表达能力较低，并且效率可能较低。 
// 在C++14中，没有std::bind的合理用例。 但是，在C++11中，
// 可以在两个受约束的情况下证明使用std::bind是合理的：
//1.移动捕获。C++11的lambda不提供移动捕获，但是可以通过结合lambda和std::bind来模拟。 
//              有关详细信息，请参阅Item32，该条款还解释了在C++14中，lambda对初始化捕获的支持消除了这个模拟的需求。
//2.多态函数对象。因为bind对象上的函数调用运算符使用完美转发，
// 所以它可以接受任何类型的实参（以Item30中描述的完美转发的限制为界限）。
// 当你要绑定带有模板化函数调用运算符的对象时，此功能很有用。 例如这个类 PolyWidget，

