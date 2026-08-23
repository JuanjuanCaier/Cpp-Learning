#include <iostream>
#include <utility>
using namespace std;

class MyBuffer
{
public:
    MyBuffer(size_t s) { cout << "构造" << endl; }
    MyBuffer(const MyBuffer &other) { cout << "拷贝构造" << endl; }
    MyBuffer(MyBuffer &&other) noexcept { cout << "移动构造 (零成本)" << endl; }
};

// 完美转发工厂
template <typename T>
MyBuffer createWrapper(T &&param) // 参数类型是万能引用
{
    // 这里的 forward 会完美地保持 param 的“左右值属性”
    return MyBuffer(forward<T>(param));
}

int main()
{
    MyBuffer buf(10);

    cout << "--- 传入左值 (buf) ---" << endl;
    auto b1 = createWrapper(buf); // 触发拷贝构造（因为 buf 是左值）

    cout << "--- 传入右值 (move(buf)) ---" << endl;
    auto b2 = createWrapper(move(buf)); // 触发移动构造

    return 0;
}

/*
构造
--- 传入左值 (buf) ---
拷贝构造
--- 传入右值 (move(buf)) ---
移动构造 (零成本)
*/

/*
完美转发的原理是：
template<typename T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept {
    return static_cast<T&&>(arg);
}

当接收左值时，例如int，推导为int&，最后的int& &&会被折叠为int&，所以forward返回左值引用。
当接收右值时，例如int，推导为int，最后的int &&不会折叠，所以forward返回右值引用。
*/