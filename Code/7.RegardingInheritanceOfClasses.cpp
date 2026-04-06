#include <iostream>

using namespace std;

// 基类A
class A
{
private:
    int a;

protected:
    int b;

public:
    int c;

    void Print()
    {
        cout << "a: " << a << endl;
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
    }

    // A 可以访问自己的所有变量。
    // A 的子类可以访问 A 的 protected 成员 b 和 public 成员 c，但不能访问 private 成员 a。
    // 外部可以访问 A 的 public 成员 c，但不能访问 A 的 protected 成员 b 和 private 成员 a。
};

class B : public A
{
    // B 继承了 A 所有的成员变量和函数，并且权限没有变化。
    // B 可以访问 protected 成员 b 和 public 成员 c，但不能访问 private 成员 a，因为 A 不给 B 权限。
    // B 的子类可以访问 protected 成员 b 和 public 成员 c，但不能访问 private 成员 a，因为 B 没有权限，也就无法给它的子类权限。
    // 外部可以访问 public 成员 c，但不能访问 protected 成员 b 和 private 成员 a。
    void Print()
    {
        // cout << "a: " << a << endl; B 不能访问 a,因为 A 不给 B 权限。
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
    }
};

class C : protected A
{
    // C 继承了 A 所有的成员变量和函数，并且权限上限为 protected。
    // C 可以访问 protected 成员 b 和 public 成员 c，但不能访问 private 成员 a，因为 A 不给 C 权限。
    // C 的子类可以访问 protected 成员 b 和 protected 成员 c，但不能访问 private 成员 a,因为 C 没有权限，也就无法给它的子类权限。
    // 外部不能访问任何成员，因为它们都是 protected。
    void Print()
    {
        // cout << "a: " << a << endl; C 不能访问 a,因为 A 不给 C 权限。
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
    }
};

class D : private A
{
    // D 继承了 A 所有的成员变量和函数，并且权限上限为 private。
    // D 可以访问 protected 成员 b 和 public 成员 c，但不能访问 private 成员 a，因为 A 不给 D 权限。
    // D 的子类不能访问任何成员，因为它们都是 private，D 不给它的子类权限。
    // 外部不能访问 D 的任何成员，因为它们都是 private。
    void Print()
    {
        // cout << "a: " << a << endl; D 不能访问 a,因为 A 不给 D 权限。
        cout << "b: " << b << endl;
        cout << "c: " << c << endl;
    }
};

int main()
{
    B b;
    C c;
    D d;

    // 外部访问
    b.c = 10; // B 的 public 成员 c 可以被访问。
    // c.c = 20; // C 的 protected 成员 c 不可以被访问，它们在继承时被 c 设定为protected。
    // d.c = 30; // D 的 private 成员 c 不可以被访问，它们在继承时被 d 设定为private。
    return 0;
}
