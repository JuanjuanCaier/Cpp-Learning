#include <iostream>
#include <memory> // 智能指针头文件
#include <vector>

using namespace std;

class Test
{
public:
    int value;
    Test(int v = 0) : value(v)
    {
        cout << "构造 Test(" << value << ")" << endl;
    }
    ~Test()
    {
        cout << "析构 Test(" << value << ")" << endl;
    }
    void print() const
    {
        cout << "value = " << value << endl;
    }
};

int main()
{
    cout << "=== unique_ptr 示例 ===" << endl;
    // 方式1：使用 make_unique
    unique_ptr<Test> up1 = make_unique<Test>(100);
    up1->print(); // 像原始指针一样使用 -> 和 *

    // 不能拷贝！下面这行会编译报错：
    // unique_ptr<Test> up2 = up1;

    // 但可以移动（转移所有权）：
    unique_ptr<Test> up2 = move(up1);
    if (up1 == nullptr)
    {
        cout << "up1 已经被转移，变为空指针" << endl;
    }
    up2->print(); // up2 现在拥有对象

    // 离开作用域时，up2 自动析构，Test(100) 自动释放

    cout << "\n=== shared_ptr 示例 ===" << endl;
    shared_ptr<Test> sp1 = make_shared<Test>(200); // 引用计数 = 1
    shared_ptr<Test> sp2 = sp1;                    // 拷贝，引用计数变为 2
    shared_ptr<Test> sp3 = sp1;                    // 引用计数变为 3

    cout << "当前引用计数: " << sp1.use_count() << endl;
    sp1->print();

    // sp1, sp2, sp3 都指向同一个对象。当最后一个 sp3 离开作用域时，才调用析构函数。
    // 为了演示，我们手动重置 sp3，让计数减少：
    sp3.reset(); // 释放 sp3 的持有权，引用计数减为 2
    cout << "reset sp3 后，引用计数: " << sp1.use_count() << endl;

    cout << "\n=== weak_ptr 简单演示 ===" << endl;
    weak_ptr<Test> wp = sp1; // 不增加引用计数
    cout << "sp1 引用计数仍为: " << sp1.use_count() << endl;

    // 使用 weak_ptr 前，需要先 lock() 转为 shared_ptr 才能访问
    if (auto sp_tmp = wp.lock())
    {
        cout << "weak_ptr 成功锁定，值为: " << sp_tmp->value << endl;
        cout << "sp1 引用计数为: " << sp1.use_count() << endl;
    }

    // 当离开作用域时，引用计数自动减少，sp_tmp释放
    cout << "sp1 引用计数为: " << sp1.use_count() << endl;

    // 函数结束，sp1, sp2 自动销毁，引用计数归零，Test(200) 自动析构
    return 0;
}

/*
=== unique_ptr 示例 ===
构造 Test(100)
value = 100
up1 已经被转移，变为空指针
value = 100

=== shared_ptr 示例 ===
构造 Test(200)
当前引用计数: 3
value = 200
reset sp3 后，引用计数: 2

=== weak_ptr 简单演示 ===
sp1 引用计数仍为: 2
weak_ptr 成功锁定，值为: 200
sp1 引用计数为: 3
sp1 引用计数为: 2
析构 Test(200)
析构 Test(100)
*/