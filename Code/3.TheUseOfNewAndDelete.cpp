#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout << "构造函数被调用。" << endl;
    }

    ~A()
    {
        cout << "析构函数被调用。" << endl;
    }
};

int main()
{
    cout << "单个对象的内存管理。" << endl;
    A *p1 = new A();
    delete p1;
    p1 = nullptr;

    cout << "对象数组的内存管理。" << endl;
    A *p2 = new A[3];
    delete[] p2;
    p2 = nullptr;

    cout << "基本数据类型的动态分配。" << endl;
    int *p3 = new int(20);
    cout << "动态分配的 int 值: " << *p3 << endl;
    delete p3;
    p3 = nullptr;

    int *p4 = new int[5]{10, 20, 30, 40, 50};
    cout << "动态分配的 int 数组: ";
    for (int i = 0; i < 5; ++i)
    {
        cout << p4[i] << " ";
    }
    cout << endl;
    delete[] p4;
    p4 = nullptr;

    return 0;
}

/*
The expected outcome is:
单个对象的内存管理。
构造函数被调用。
析构函数被调用。
对象数组的内存管理。
构造函数被调用。
构造函数被调用。
构造函数被调用。
析构函数被调用。
析构函数被调用。
析构函数被调用。
基本数据类型的动态分配。
动态分配的 int 值: 20
动态分配的 int 数组: 10 20 30 40 50
*/