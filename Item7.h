#pragma once
#include <iostream>

//Item 7: Distinguish between () and {} when creating objects
namespace Item7 {
    class Demo {
    public:
        class MyClass {
        public:
            // Default constructor
            MyClass() {
                std::cout << "Default constructor\n";
            }

            // Constructor with an int argument
            MyClass(int x) {
                std::cout << "Constructor with parameter: " << x << std::endl;
            }
        };
        class Widget {
        public:
            Widget(int i, bool b) {};                      //同之前一样
            Widget(int i, double d) {};                    //同之前一样
            //Widget(std::initializer_list<bool> il) {};     //现在元素类型为bool
            Widget(std::initializer_list<std::string> il) {};
        };
        void run() {
            // 1. Default constructor and function declaration bug
            MyClass obj1();  // This declares a function, not an object
            MyClass obj2{};   // Correct: initializes an object
            //MyClass obj1;  // This declares a function, not an object

            // 2. Constructor with parameters
            MyClass obj3(42);  // This works
            MyClass obj4{ 42 };   // This also works

            // 3. List initialization - prevents narrowing conversions
            double pi = 3.14159;
            int intPi1 = pi;     // Implicit narrowing, works fine
            //int intPi2{ pi };      // Error: narrowing conversion is not allowed

            Widget w{ 10, 5.0 };//错误！要求变窄转换
        }
    };
}
