#include <iostream>
#include "type.h"

namespace Item1 {
    class Demo {
    public:
        template<typename T>
        void passByValue(T param) {
            std::cout << "[passByValue] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passByRef(T& param) {
            std::cout << "[passByRef] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passByUniversalRef(T&& param) {
            std::cout << "[passByUniversalRef] T = " << printType<T>() << "\n";
        }

        template<typename T>
        void passArrayOrFunc(T param) {
            std::cout << "[passArrayOrFunc] T = " << printType<T>() << "\n";
        }

        static void sampleFunction(int) {}

        void run() {
            int x = 42;
            const int cx = x;
            const int& rx = x;

            std::cout << "--- Item1: passByValue ---\n";
            passByValue(x);
            passByValue(cx);
            passByValue(rx);

            std::cout << "--- Item1: passByRef ---\n";
            passByRef(x);
            passByRef(cx);
            passByRef(rx);

            std::cout << "--- Item1: passByUniversalRef ---\n";
            passByUniversalRef(x);
            passByUniversalRef(cx);
            passByUniversalRef(42);

            std::cout << "--- Item1: passArrayOrFunc ---\n";
            const char arr[] = "hello";
            passArrayOrFunc(arr);
            passArrayOrFunc(&sampleFunction);  // 明确传函数指针
        }
    };
}