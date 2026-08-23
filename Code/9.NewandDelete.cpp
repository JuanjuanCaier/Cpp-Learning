#include <iostream>
#include <new>

using namespace std;

// 一个简单的测试类，方便观察构造和析构
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
};

int main()
{
    cout << "--- 1. 单个对象 ---" << endl;
    Test *pSingle = new Test(100); // 动态分配一个 Test 对象，并调用构造函数
    cout << "值: " << pSingle->value << endl;
    delete pSingle; // 释放对象，调用析构函数

    cout << "\n--- 2. 数组 ---" << endl;
    int n = 3;
    Test *pArray = new Test[n]; // 动态分配 n 个 Test 对象（默认构造）
    for (int i = 0; i < n; ++i)
    {
        pArray[i].value = i * 10; // 修改值以便观察
        cout << "pArray[" << i << "].value = " << pArray[i].value << endl;
    }
    delete[] pArray; // 释放数组，注意必须用 delete[]

    cout << "\n--- 3. Placement new ---" << endl;
    // 先分配一块原始内存
    char *buffer = new char[2 * sizeof(Test)];
    cout << "已分配原始内存缓冲区（地址: " << (void *)buffer << "）" << endl;

    // 在这块内存上构造
    Test *pPlace1 = new (buffer) Test(1);
    cout << "placement new1 构造的对象值: " << pPlace1->value << endl;
    Test *pPlace2 = new (buffer + sizeof(Test)) Test(2);
    cout << "placement new2 构造的对象值: " << pPlace2->value << endl;

    // 显式调用析构函数（placement new 的对象不能直接用 delete）
    pPlace1->~Test();
    pPlace2->~Test();

    // 释放原始内存
    delete[] buffer;
    cout << "原始内存已释放" << endl;

    return 0;
}

/*
--- 1. 单个对象 ---
构造 Test(100)
值: 100
析构 Test(100)

--- 2. 数组 ---
构造 Test(0)
构造 Test(0)
构造 Test(0)
pArray[0].value = 0
pArray[1].value = 10
pArray[2].value = 20
析构 Test(20)
析构 Test(10)
析构 Test(0)

--- 3. Placement new ---
已分配原始内存缓冲区（地址: 0x6ae830）
构造 Test(1)
placement new1 构造的对象值: 1
构造 Test(2)
placement new2 构造的对象值: 2
析构 Test(1)
析构 Test(2)
原始内存已释放
*/