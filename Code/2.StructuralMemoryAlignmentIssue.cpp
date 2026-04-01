#include <iostream>

using namespace std;

struct A
{
    int A1;
    int A2;
};

struct alignas(8) B
{
    int B1;
};

int main()
{
    A a;
    B b;

    cout << "结构体的内存地址和第一个成员地址一样，例如 a 的地址为 " << &a << " ，而它的第一个成员 A1 的地址为 " << &a.A1 << " 。" << endl;
    cout << "alignof 可以计算出对齐方式，例如 a 的对齐方式为 " << alignof(a) << " 字节。" << endl;
    cout << "alignas 可以指定对齐方式， B 的对齐被指定为 " << alignof(b) << " 字节，所以它的大小为 " << sizeof(b) << " 字节，即使它只有一个大小为 " << sizeof(b.B1) << " 字节的成员。" << endl;
}

/*
The expected outcome is:
结构体的内存地址和第一个成员地址一样，例如 a 的地址为 0x5ffe88 ，而它的第一个成员 A1 的地址为 0x5ffe88 。
alignof 可以计算出对齐方式，例如 a 的对齐方式为 4 字节。
alignas 可以指定对齐方式， B 的对齐被指定为 8 字节，所以它的大小为 8 字节，即使它只有一个大小为 4 字节的成员。
*/