#include <iostream>
#include <cstdlib>

using namespace std;

class A
{
public:
    A()
    {
        cout << "全局变量构造进行。" << endl;
    }
    ~A()
    {
        cout << "全局变量析构进行。" << endl;
    }
};
A a;

class B
{
public:
    B()
    {
        cout << "static变量构造进行。" << endl;
    }

    ~B()
    {
        cout << "static变量析构进行。" << endl;
    }
};

// 加上这个属性，函数会自动在 main 之后运行
__attribute__((destructor)) void C()
{
    cout << "GCC 扩展 destructor 执行。" << endl;
}

void D()
{
    cout << "先定义的atexit函数后执行。" << endl;
}

void E()
{
    cout << "后定义的atexit函数先执行。" << endl;
}

class F
{
public:
    F()
    {
        cout << "普通局部变量构造进行。" << endl;
    }
    ~F()
    {
        cout << "普通局部变量析构进行。" << endl;
    }
};

int main()
{
    cout << "main执行。" << endl;
    static B b;
    F f;

    atexit(D);
    atexit(E);

    cout << "main结束。" << endl;
    return 0;
}