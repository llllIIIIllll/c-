#include <iostream>
#include <vector>
#include <cassert>

#include <boost/te.hpp>

namespace te = boost::te;

// Define interface of something which is drawable
struct Drawable
{
    void draw(std::ostream &out) const
    {
        te::call([](auto const &self, auto &out) { self.draw(out); }, *this, out);
    }
};

// Define implementation which is drawablw (No inheritance)
struct Square
{
    void draw(std::ostream &out) const { out << "Square\n"; }

    void draw(std::ostream &out, const std::string &v) const 
    {
        out << v << "::Square";
    }
};

struct Circle
{
    void draw(std::ostream &out) const { out << "Circle\n"; }

    void draw(std::ostream &out, const std::string &v) const 
    {
        out << v << "::Circle";
    }
};

// Define 
void draw(te::poly<Drawable> const &drawable) { drawable.draw(std::cout); }

#ifdef ERASE
// erase + declare it
struct Drawable : te::poly<Drawable> 
{
    using te::poly<Drawable>::poly;

    void draw(std::ostream &out) const 
    {
        te::call([](auto const &self, auto &out) {self.draw(out); }, *this, out);
    }
};
#else
#endif

// Overload it
struct Addable 
{
    constexpr auto add(int i)        { return te::call<int>(add_impl, *this,  i); }
    constexpr auto add(int a, int b) { return te::call<int>(add_impl, *this, a, b); }

private:
    static constexpr auto add_impl = [](auto &self, auto... args)
    {
        return self.add(args...);
    };
};

class Calc 
{
public:
    constexpr auto add(int i)        { return i; }
    constexpr auto add(int a, int b) { return a + b; }
};

// Override it
namespace v1
{
    struct Drawable 
    {
        void draw(std::ostream &out) const 
        {
            te::call([](auto const &self, auto &&... args) { self.draw(args...); },
                    *this, out, "v1");
        }
    };

} // namespace v1

namespace v2
{
    struct Drawable : v1::Drawable 
    {
        Drawable() { te::extends<v1::Drawable>(*this); }

        // override
        void draw(std::ostream &out) const 
        {
            te::call([](auto const &self, auto && ... args) { self.draw(args...); },
                    *this, out, "v2");
        }

        // extend/overload
        void draw(std::ostream&out, int minor) const 
        {
            te::call([](auto const &self, auto && ... args) { self.draw(args...); },
                    *this, out, "v2" + std::to_string(minor));
        }
    };
} // namespace v2

template <class T, class... Ts>
void draw(te::poly<T> const &drawable, const Ts... args)
{
    drawable.draw(std::cout, args...);
}

int main()
{
    // Call draw polymorphically 
    draw(Circle{});
    draw(Square{});

    std::vector<te::poly<Drawable>> drawables{};

    drawables.push_back(Square{});
    drawables.push_back(Circle{});

    for (const auto &drawable : drawables)
        drawable.draw(std::cout); // prints Square Circle

    te::poly<Addable> addable{Calc{}};
    assert(3 == addable.add(3));
    assert(3 == addable.add(1, 2));

    std::cout << std::endl;
    draw<v1::Drawable>(Circle{});
    draw<v1::Drawable>(Square{});

    draw<v2::Drawable>(Circle{});
    draw<v2::Drawable>(Circle{}, 1);

    draw<v2::Drawable>(Square{});
    draw<v2::Drawable>(Square{}, 2);

    std::cout << std::endl;
}
