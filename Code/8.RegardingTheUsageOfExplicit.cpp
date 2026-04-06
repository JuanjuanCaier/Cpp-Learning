#include <iostream>

using namespace std;

class A
{
public:
    int a;

    A(int _a)
    {
        a = _a;
    }
};

// 错误！类外定义不能加explicit，编译会报错
// explicit A::A(int val) : a(val) {}

class B
{
public:
    int b;
    explicit B(int _b)
    {
        b = _b;
    }
};

void TestA(A a)
{
    cout << a.a << endl;
}

void TestB(B b)
{
    cout << b.b << endl;
}

int main()
{
    A a(1);
    a = 2;
    TestA(3);

    B b(1);
    // b = 2;错误，由于 explicit 关键字，此处无法隐式构造临时变量
    b = B(2);

    // TestB(3);错误，由于 explicit 关键字，此处无法隐式构造临时变量
    TestB(B(3));
    TestB(static_cast<B>(3));

    return 0;
}

/*
预期输出：
3
3
3
*/