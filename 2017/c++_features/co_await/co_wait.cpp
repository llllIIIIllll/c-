template <typename P, typename T>
decltype(auto) get_awaitable(P& promise, T&& expr)
{
	if constexpr(has_any_await_transform_member_v<P>)
		return promise.await_transform(static_cast<T&&>(expr));
	else
		return static_cast<T&&>(expr);
}

template <typename Awaitable>
decltype(auto) get_awaiter(Awaitable&& awaitable)
{
	if constexpr(has_member_operator_co_await_v<Awaitable>)
		return static_cast<Awaitable&&>(awaitable).operator co_await();
	else if constexpr(has_non_member_operator_co_await_v<Awaitable&&>)
		return operator co_await(static_cast<Awaitable&&>(awaitable));
	else
		return static_cast<Awaitable&&>(awaitable);
}
