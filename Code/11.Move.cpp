#include <iostream>
#include <utility> // move
using namespace std;

class MyBuffer
{
private:
    int *data; // 指向堆内存的指针
    size_t size;

public:
    // 构造函数（分配内存）
    MyBuffer(size_t s) : size(s), data(new int[s])
    {
        cout << "构造: 分配了 " << size << " 个 int" << endl;
    }

    // 析构函数（释放内存）
    ~MyBuffer()
    {
        if (data)
        {
            cout << "析构: 释放了 " << size << " 个 int" << endl;
            delete[] data;
            data = nullptr;
        }
        else
        {
            cout << "析构: 对象为空，无需释放" << endl;
        }
    }

    // ---- 拷贝构造函数（深拷贝，耗时） ----
    MyBuffer(const MyBuffer &other) : size(other.size), data(new int[other.size])
    {
        cout << "拷贝构造: 深复制了 " << size << " 个 int (耗时)" << endl;
        for (size_t i = 0; i < size; ++i)
            data[i] = other.data[i]; // 复制数据
    }

    // ---- 移动构造函数（偷资源，零成本） ----
    // noexcept告诉编译器这个函数不会抛出异常，放心使用资源
    MyBuffer(MyBuffer &&other) noexcept
        : size(other.size), data(other.data)
    { // 直接偷走指针！
        cout << "移动构造: 偷走了资源 (零成本)" << endl;
        // 关键一步：把 other 的指针置空，防止它析构时把内存释放掉！
        other.data = nullptr;
        other.size = 0;
    }

    // 一个简单的设置数据方法
    void set(int val)
    {
        if (data)
            data[0] = val;
    }
    void print() const
    {
        if (data)
            cout << "data[0] = " << data[0] << endl;
    }

    bool isEmpty() const { return data == nullptr; }
};

int main()
{
    cout << "===== 1. 拷贝构造（复制） =====" << endl;
    MyBuffer buf1(10); // 构造
    buf1.set(999);
    MyBuffer buf2 = buf1; // 调用拷贝构造（深复制）
    buf1.print();
    buf2.print();

    cout << "\n===== 2. 移动构造（转移） =====" << endl;
    MyBuffer buf3 = move(buf1); // 调用移动构造（偷资源）

    // 此时 buf1 已经被“掏空”，变成了空壳子
    cout << "buf1 被移动后，是否为空？ " << (buf1.isEmpty() ? "是" : "否") << endl;
    // 为了演示，在 MyBuffer 里加个判空太麻烦，我们直接看执行结果：
    // 注意：buf1 析构时因为 data=nullptr，不会重复释放内存，程序安全！

    cout << "buf3 的数据: ";
    buf3.print();

    return 0;
}

/*
===== 1. 拷贝构造（复制） =====
构造: 分配了 10 个 int
拷贝构造: 深复制了 10 个 int (耗时)
data[0] = 999
data[0] = 999

===== 2. 移动构造（转移） =====
移动构造: 偷走了资源 (零成本)
buf1 被移动后，是否为空？ 是
buf3 的数据: data[0] = 999
析构: 释放了 10 个 int
析构: 释放了 10 个 int
析构: 对象为空，无需释放
*/

/*
注意，move返回的是一个右值引用，所以原值还是否能用完成取决于接受它的对象的移动构造函数
*/