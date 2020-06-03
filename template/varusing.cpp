#include <type_traits>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

class Customer
{
private:
    std::string name;
public:
    Customer(std::string const& n) : name(n) {}
    std::string getName() const { return name; }
};

struct CustomerEq
{
    bool operator() (Customer const& c1, Customer const& c2) const
    { return c1.getName() == c2.getName(); }
};

struct CustomerHash
{
    std::size_t operator() (Customer const& c) const 
    { return std::hash<std::string>()(c.getName()); }
};

template<typename... Bases>
struct Overloader : Bases...
{
    using Bases::operator()...;
};

int main()
{
    using CustomerOP = Overloader<CustomerHash, CustomerEq>;
    std::unordered_set<Customer, CustomerHash, CustomerEq> coll1;
    std::unordered_set<Customer, CustomerOP, CustomerOP> coll2;
    Customer c1("Tom");
    Customer c2("Tom");
    coll1.insert(c1);
    coll1.insert(c2);
    std::cout << coll1.size();
    std::cout << std::endl;
    for (auto t : coll1)
    {
        std::cout << t.getName();
    }
    std::cout << std::endl;
    
    coll2.insert(c1);
    coll2.insert(c2);
    std::cout << coll2.size();
    std::cout << std::endl;
    for (auto t : coll2)
    {
        std::cout << t.getName();
    }
    std::cout << std::endl;
}