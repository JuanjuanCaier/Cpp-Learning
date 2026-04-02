#include <iostream>
using namespace std;

int A(int a)
{
    return a + 1;
}

int *B(int n)
{
    static int val = n; // 静态变量，返回地址有效
    return &val;
}

int main()
{

    // 数组里存了 10 个指向int的指针
    cout << "int *p[10]" << endl;
    int a = 10, b = 20, c = 30;
    int *p1[10];

    p1[0] = &a;
    p1[1] = &b;
    p1[2] = &c;

    cout << "p1[0] 指向的值：" << *p1[0] << endl;
    cout << "p1[0] 的值：" << p1[1] << endl;

    // 数组里存了10个int
    int C[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int (*p2)[10] = &C;

    // 通过数组指针访问数组元素
    cout << "数组第1个元素：" << (*p2)[0] << endl;
    cout << "数组第5个元素：" << (*p2)[4] << endl;

    // 一个函数声明
    int *p3 = B(123); // 调用函数，接收返回的int指针
    cout << "函数返回的指针指向的值：" << *p3 << endl;

    // 指向参数为int、返回值为int的函数的指针
    int (*p4)(int) = A;
    cout << "函数指针调用，结果：" << p4(5) << endl;

    return 0;
}

/*
The expected outcome is:
int *p[10]
p1[0] 指向的值：10
p1[0] 的值：0x5ffe60（每次都会变）
数组第1个元素：0
数组第5个元素：4
函数返回的指针指向的值：123
函数指针调用，结果：6
*/