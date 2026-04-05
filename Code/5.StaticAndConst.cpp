#include <iostream>
using namespace std;

// 全局非static变量：默认外部链接，可被其他编译单元引用
int a = 10;
// 全局static变量：内部链接，仅当前文件可见，实现隐藏作用；未初始化默认置0
static int b;
// 全局const变量：内部链接，仅当前文件可见，和static有相同的隐藏作用，多文件包含无符号冲突
const int c = 100;

// 全局非static函数：默认外部链接，可被其他编译单元调用
void d() {}
// 全局static函数：内部链接，仅当前文件可调用，实现隐藏作用
static void e() {}

// 演示函数内静态变量：仅初始化一次，具备记忆性，生命周期贯穿程序全程，作用域仅限函数内
void f()
{
    // 局部静态变量：未初始化默认置0，存储在全局区
    static int g;
    // 仅第一次调用f时执行初始化，后续调用跳过初始化，具备记忆性
    static int h = 1;
    h++;
    cout << "函数f内静态变量h的值：" << h << endl;
}

// 演示const基础特性
void i()
{
    // const常量必须在定义时初始化，初始化后不可修改
    const int j = 10;
    // j = 20; // 错误：const修饰的变量不可修改
    cout << "const常量j的值：" << j << endl;
}

// 演示const形参：可接收const和非const类型的实参
void k(const int &l)
{
    // l = 10; // 错误：const引用形参不可修改
    cout << "const形参l的值：" << l << endl;
}

// 测试const形参的传参兼容性
void m()
{
    int n = 20;
    const int o = 30;
    k(n); // 传入非const实参
    k(o); // 传入const实参
}

class A
{
public:
    // const成员变量：不可在类外初始化，必须通过构造函数初始化列表初始化
    const int p;
    // mutable成员变量：可在const成员函数中被修改
    mutable int q;
    // static成员变量：与类关联，不与对象关联，类内声明，必须类外初始化
    static int r;

    // 构造函数：必须通过初始化列表初始化const成员变量p
    A(int val) : p(val) {}

    // static成员函数：无this指针，不可访问类的非static成员
    static void s()
    {
        // p = 10; // 错误：static成员函数无法访问非static成员变量
        // q = 20; // 错误：static成员函数无法访问非static成员变量
        r = 200; // 正确：可访问同属类的static成员变量
        cout << "static成员函数s执行，static成员r的值：" << r << endl;
    }

    // 错误示例：static成员函数不可被声明为const、虚函数、volatile
    // static void t() const {} // 错误：static函数不能声明为const
    // virtual static void u() {} // 错误：static函数不能声明为虚函数
    // static void v() volatile {} // 错误：static函数不能声明为volatile

    // 非static成员函数：可访问static和非static成员，可调用static成员函数
    void w()
    {
        int tmp = p; // 访问非static const成员
        r = 300;     // 访问static成员
        s();         // 调用static成员函数
        cout << "非static成员函数w执行，const成员p的值：" << tmp << endl;
    }

    // const成员函数：不可修改非mutable的成员变量
    void x() const
    {
        // p = 100; // 错误：const成员函数不可修改非mutable的成员
        q = 200; // 正确：mutable修饰的成员可在const函数中修改
        r = 400; // 正确：static成员不属于对象，不受const函数限制
        s();     // 正确：可调用static成员函数
        cout << "const成员函数x执行，mutable成员q的值：" << q << endl;
    }

    // 非const成员函数：const对象不可调用
    void y()
    {
        cout << "非const成员函数y执行" << endl;
    }
};

// static成员变量类外初始化：无需加static关键字，必须在类定义外完成
int A::r = 100;

// 演示类中static和const的核心特性
void z()
{
    // 非const对象
    A a1(10);
    // 非const对象可调用const和非const成员函数
    a1.w();
    a1.x();
    a1.y();

    // const对象
    const A a2(20);
    // const对象仅可调用const成员函数
    a2.x();
    // a2.w(); // 错误：const对象不可调用非const成员函数
    // a2.y(); // 错误：const对象不可调用非const成员函数

    // static成员变量/函数可通过类名直接访问，无需创建对象
    A::r = 500;
    A::s();
    // 也可通过对象访问static成员
    a1.r = 600;
    a1.s();
}

int main()
{
    cout << "全局static变量默认初始化测试。" << endl;
    cout << "全局static变量b默认值：" << b << endl;

    cout << "函数内静态变量记忆性测试" << endl;
    f();
    f();
    f();

    cout << "const基础特性测试" << endl;
    i();

    cout << "const形参兼容性测试" << endl;
    m();

    cout << "类内static与const特性测试" << endl;
    z();

    return 0;
}

/*
全局static变量默认初始化测试。
全局static变量b默认值：0
函数内静态变量记忆性测试
函数f内静态变量h的值：2
函数f内静态变量h的值：3
函数f内静态变量h的值：4
const基础特性测试
const常量j的值：10
const形参兼容性测试
const形参l的值：20
const形参l的值：30
类内static与const特性测试
static成员函数s执行，static成员r的值：200
非static成员函数w执行，const成员p的值：10
static成员函数s执行，static成员r的值：200
const成员函数x执行，mutable成员q的值：200
非const成员函数y执行
static成员函数s执行，static成员r的值：200
const成员函数x执行，mutable成员q的值：200
static成员函数s执行，static成员r的值：200
static成员函数s执行，static成员r的值：200

/////////////////////////////////////////////

任何变量 / 函数，只需要三个问题确定特性：

它存在哪个内存区？
全局 / 静态区 → 生命周期全程
栈区 → 函数结束销毁


有没有被 static 修饰？
全局：变内部链接（仅当前文件用）
局部：从栈区 → 全局区（永久内存 + 记忆性）


有没有被 const 修饰？
加只读锁 → 不能修改
const 对象 / 函数 → 保证不修改内存
*/