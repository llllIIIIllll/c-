#include <iostream>

typedef enum productType
{
    A_Type,
    B_Type,
    C_Type,
} PRODUCTTYPE;

class product
{
public:
    virtual void show() = 0;
};

class A : public product
{
public:
    void show() { std::cout << " A " << std::endl; }
};
class B : public product
{
public:
    void show() { std::cout << " B " << std::endl; }
};
class C : public product
{
public:
    void show() { std::cout << " C " << std::endl; }
};

class ProductFactory
{
public:
    product* createProduct(PRODUCTTYPE type)
    {
        switch (type)
        {
        case A_Type:
            return new A();
            break;
        case B_Type:
            return new B();
            break;
        case C_Type:
            return new C();
            break;
        default:
            return new A();
            break;
        }
    }
};

int main()
{

    ProductFactory pf;
    product* a = pf.createProduct(A_Type);
    product* b = pf.createProduct(B_Type);
    product* c = pf.createProduct(C_Type);
}