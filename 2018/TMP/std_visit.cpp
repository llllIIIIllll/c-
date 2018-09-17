#include <iostream>
#include <variant>

using namespace std;

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct Fluid       { };
struct LightItem   { };
struct HeavyItem   { };
struct FragileItem { };

struct VisitPackage
{
    void operator()(Fluid       &) { cout << "Fluid      \n"; }
    void operator()(LightItem   &) { cout << "LightItem  \n"; }
    void operator()(HeavyItem   &) { cout << "HeavyItem  \n"; }
    void operator()(FragileItem &) { cout << "FragileItem\n"; }
};

int main()
{
    std::variant<Fluid, LightItem, HeavyItem, FragileItem> package {
        FragileItem()
    };

    std::visit(VisitPackage(),  package);

    std::variant<LightItem, HeavyItem> basicPackA;
    std::variant<LightItem, HeavyItem> basicPackB;

    std::visit(overloaded {
        [](LightItem&, LightItem&) { cout << "2 light items\n";       },
        [](LightItem&, HeavyItem&) { cout << "light & heavy items\n"; },
        [](HeavyItem&, LightItem&) { cout << "heavy & light items\n"; },
        [](HeavyItem&, HeavyItem&) { cout << "2 heavy items\n";       },
        },  basicPackA, basicPackB );
}
