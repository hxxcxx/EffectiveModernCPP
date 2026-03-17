/**
 * @file smart_pointer_basics.cpp
 * @brief 智能指针基础示例
 * 
 * 本示例演示了C++智能指针的基本用法：
 * - std::unique_ptr：独占所有权
 * - std::shared_ptr：共享所有权
 * - std::weak_ptr：避免循环引用
 * 
 * 编译运行:
 *   g++ -std=c++17 smart_pointer_basics.cpp -o smart_pointer_basics
 *   ./smart_pointer_basics
 */

#include <iostream>
#include <memory>
#include <vector>
#include <string>

/**
 * @brief 简单的Widget类，用于演示智能指针
 */
class Widget {
public:
    Widget(int id) : id_(id) {
        std::cout << "Widget " << id_ << " 构造\n";
    }
    
    ~Widget() {
        std::cout << "Widget " << id_ << " 析构\n";
    }
    
    void doSomething() {
        std::cout << "Widget " << id_ << " 做某事\n";
    }
    
    int getId() const { return id_; }

private:
    int id_;
};

/**
 * @brief 演示std::unique_ptr的用法
 */
void demoUniquePtr() {
    std::cout << "\n=== std::unique_ptr 示例 ===\n";
    
    // 创建unique_ptr
    auto ptr1 = std::make_unique<Widget>(1);
    ptr1->doSomething();
    
    // unique_ptr不可复制，但可以移动
    auto ptr2 = std::move(ptr1);
    // ptr1现在为nullptr
    if (!ptr1) {
        std::cout << "ptr1已移动，现在为空\n";
    }
    
    ptr2->doSomething();
    
    // 自定义删除器
    auto deleter = [](Widget* p) {
        std::cout << "使用自定义删除器删除Widget " << p->getId() << "\n";
        delete p;
    };
    std::unique_ptr<Widget, decltype(deleter)> ptr3(new Widget(3), deleter);
}

/**
 * @brief 演示std::shared_ptr的用法
 */
void demoSharedPtr() {
    std::cout << "\n=== std::shared_ptr 示例 ===\n";
    
    // 创建shared_ptr
    auto ptr1 = std::make_shared<Widget>(1);
    std::cout << "引用计数: " << ptr1.use_count() << "\n";  // 1
    
    {
        auto ptr2 = ptr1;  // 复制，引用计数增加
        std::cout << "引用计数: " << ptr1.use_count() << "\n";  // 2
        
        ptr2->doSomething();
    }
    // ptr2离开作用域，引用计数减少
    std::cout << "引用计数: " << ptr1.use_count() << "\n";  // 1
}

/**
 * @brief 演示std::weak_ptr的用法
 */
void demoWeakPtr() {
    std::cout << "\n=== std::weak_ptr 示例 ===\n";
    
    auto ptr1 = std::make_shared<Widget>(1);
    std::weak_ptr<Widget> weakPtr = ptr1;
    
    std::cout << "引用计数: " << ptr1.use_count() << "\n";  // 1 (weak_ptr不影响引用计数)
    
    // 使用lock()获取shared_ptr
    if (auto ptr2 = weakPtr.lock()) {
        std::cout << "成功获取shared_ptr，引用计数: " << ptr2.use_count() << "\n";  // 2
        ptr2->doSomething();
    }
    
    // 重置ptr1
    ptr1.reset();
    
    // 检查weak_ptr是否过期
    if (weakPtr.expired()) {
        std::cout << "weak_ptr已过期\n";
    }
}

/**
 * @brief 演示循环引用问题
 */
class Node;

// 使用shared_ptr导致的循环引用（内存泄漏）
class NodeWithSharedPtr {
public:
    NodeWithSharedPtr(int id) : id_(id) {
        std::cout << "Node " << id_ << " 构造\n";
    }
    
    ~NodeWithSharedPtr() {
        std::cout << "Node " << id_ << " 析构\n";
    }
    
    void setNext(std::shared_ptr<NodeWithSharedPtr> next) {
        next_ = next;
    }
    
private:
    int id_;
    std::shared_ptr<NodeWithSharedPtr> next_;
};

// 使用weak_ptr避免循环引用
class Node {
public:
    Node(int id) : id_(id) {
        std::cout << "Node " << id_ << " 构造\n";
    }
    
    ~Node() {
        std::cout << "Node " << id_ << " 析构\n";
    }
    
    void setNext(std::shared_ptr<Node> next) {
        next_ = next;
    }
    
private:
    int id_;
    std::weak_ptr<Node> next_;  // 使用weak_ptr避免循环引用
};

void demoCircularReference() {
    std::cout << "\n=== 循环引用示例 ===\n";
    
    // 使用shared_ptr（内存泄漏）
    std::cout << "使用shared_ptr（内存泄漏）:\n";
    {
        auto node1 = std::make_shared<NodeWithSharedPtr>(1);
        auto node2 = std::make_shared<NodeWithSharedPtr>(2);
        node1->setNext(node2);
        node2->setNext(node1);
        // 离开作用域时，node1和node2都不会被析构（内存泄漏）
    }
    std::cout << "node1和node2应该已被析构，但实际没有（内存泄漏）\n";
    
    // 使用weak_ptr（正确析构）
    std::cout << "\n使用weak_ptr（正确析构）:\n";
    {
        auto node1 = std::make_shared<Node>(1);
        auto node2 = std::make_shared<Node>(2);
        node1->setNext(node2);
        node2->setNext(node1);
        // 离开作用域时，node1和node2都会被正确析构
    }
    std::cout << "node1和node2已被正确析构\n";
}

int main() {
    std::cout << "=== 智能指针基础示例 ===\n";
    
    demoUniquePtr();
    demoSharedPtr();
    demoWeakPtr();
    demoCircularReference();
    
    std::cout << "\n=== 示例完成 ===\n";
    
    return 0;
}
