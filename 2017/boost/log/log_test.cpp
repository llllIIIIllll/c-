#include <boost\log\core.hpp>
#include <boost\log\trivial.hpp>
#include <boost\log\expressions.hpp>

namespace logging = boost::log;

void init()
{
	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);
}

int main(int, char*[])
{
	init();

	BOOST_LOG_TRIVIAL(trace)   << "A trace severity message";
	BOOST_LOG_TRIVIAL(debug)   << "A debug severity message";
	BOOST_LOG_TRIVIAL(info)    << "A information severity message";
	BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
	BOOST_LOG_TRIVIAL(error)   << "A error severity message";
	BOOST_LOG_TRIVIAL(fatal)   << "A fatal severity message";

	system("pause");
	return 0;
}
