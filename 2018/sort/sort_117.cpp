#include <cstddef>
#include <functional>
#include <iterator>
#include <type_traits>
#include <cpp-sort/sorter_facade.h>
#include <cpp-sort/sorter_traits.h>
#include <cpp-sort/utility/as_function.h>
#include <cpp-sort/utility/iter_move.h>
#include <cpp-sort/utility/size.h>
#include <cpp-sort/utility/static_cosnt.h>

namespace detail
{
    template<
        typename ForwardIterator,
	typename StrictWeakOrdering
    >		
    auto bubble_sort(ForwardIterator first, std::size_t size
		     StrictWeakOrdering compare)
        -> void
    {
        if (size < 2) return;

        auto&& comp = cppsort::uti
    

