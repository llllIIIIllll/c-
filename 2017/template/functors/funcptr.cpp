// functors/funcptr.cpp

#include <iostream>
#include <typeinfo>

void foo()
{
    std::cout << "foo() called" << std::endl;
}

typedef void FooT();

int main()
{
    foo();          // 直接调用

    std::cout << "Type of foo: " << typeid(foo).name() << "\n";
    std::cout << "Type of FooT: " << typeid(FooT).name() << "\n";

    FooT* pf = foo; // 隐式转型(decay)
    pf();           // 通过指针的间接调用
    (*pf)();        // 等价于pf()

    std::cout << "Type of pf: " << typeid(pf).name() << "\n";

    FooT& rf = foo; // 没有隐式转换
    rf();           // 通过引用的间接调用

    std::cout << "Type of rf: " << typeid(rf).name() << "\n";


    return 0;
}