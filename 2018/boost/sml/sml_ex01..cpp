#include <boost/sml.hpp>
#include <cassert>

namespace sml = boost::sml;

// MSVC not support
namespace
{
	struct e1 {};
	struct e2
	{
		bool value = true;
	};
	auto event2 = sml::event<e2>;
	struct e4
	{
		int value = 0;
	};
	struct events
	{
		auto operator()()  const noexcept
		{
			using namespace sml;
			auto guard = [](const e2& e) { return e.value; };
			return make_transition_table(
				*"idle"_s + event<e1> = "s1"_s,
				"s1"_s + event2 [guard] = "s2"_s,
				"s2"_s + "e3"_e = "s3"_s,
				"s3"_s + event<e4> / [](const auto& e) { assert(42 == e.value); } = X
			);
		}
	};
}

int main()
{
	sml::sm<events> sm;
	using namespace sml;
	sm.process_event(e1{});
	sm.process_event(e2{});
	sm.process_event("e3"_e());
	sm.process_event(e4{42});
	assert(sm.is(X));
}