#include <boost/mpl/list.hpp>

using namespace boost;

template <typename T, typename From, typename Event, typename To,
	bool (T::* transition_func)(Event const&)>
struct transition
{
	typedef	T		fsm_t;
	typedef From	from_state_t;
	typedef Event	event_t;
	typedef To		to_state_t;

	typedef typename Event::base_t base_event_t;
	static bool do_transtion(T& x, base_event_t const& e)
	{
		return (x.*transition_func)(static_assert<event_t const&>(e));
	}
};

