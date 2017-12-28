#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// member function
class printer
{
public:
	printer(boost::asio::io_context& io)
		: timer_(io, boost::posix_time::seconds(1)),
		count_(0)
	{
		timer_.async_wait(boost::bind(&printer::print, this));
	}

	~printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}

	void print()
	{
		if (count_ < 5)
		{
			std::cout << count_ << std::endl;
			++count_;

			timer_.expires_at(timer_.expires_at() + boost::posix_time::seconds(1));
			timer_.async_wait(boost::bind(&printer::print, this));
		}
	}

private:
	boost::asio::deadline_timer timer_;
	int count_;
};

// function with parameters
void print(const boost::system::error_code& /*e*/,
	boost::asio::deadline_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << std::endl;
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print,
			boost::asio::placeholders::error, t, count));
	}
}

int main()
{
	boost::asio::io_context io;

	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));
	t.async_wait(boost::bind(print,
		boost::asio::placeholders::error, &t, &count));
	io.run();
	std::cout << "Final count is " << count << std::endl;
	std::cin.get();


	// member function
	boost::asio::io_context io_1;
	printer p(io_1);
	io_1.run();
	std::cin.get();

	return 0;
}