/// The Accumulators Framework is framework for 
/// performing incremental calculations.

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>

#include <boost/ref.hpp>
#include <boost/bind.hpp>

using namespace boost::accumulators;
using namespace boost;

/// usage
void accumulator_set_1_test()
{
	accumulator_set<double, stats<tag::mean, tag::moment<2>>> acc;

	acc(1.2);
	acc(2.3);
	acc(3.7);
	acc(5.6);

	std::cout << "Mean:   " << mean(acc) << std::endl;
	std::cout << "Moment: " << moment<2>(acc) << std::endl;
}

void accumulator_set_2_test()
{
	std::vector<double> data{ 1.2, 2.3, 3.4, 4.5, 5.6, 6.7 };
	accumulator_set<double, features<tag::min, tag::mean>> acc;
	std::for_each(data.begin(), data.end(), acc);

}

void accumulator_set_3_test()
{
	std::vector<double> data{ 1.2, 2.3, 3.4, 4.5, 5.6, 6.7 };
	// if data is not cheap to copy
	accumulator_set<double, features<tag::tail<left>> > acc(
		tag::tail<left>::cache_size = 4);
	std::for_each(data.begin(), data.end(), bind<void>(ref(acc), _1));
	std::for_each(data.begin(), data.end(), [&acc](double y) {  acc(y); });
}

void accumulator_set_4_test()
{
	// Calculate the minimum and maximum for a sequence of integers.
	accumulator_set<int, features<tag::min, tag::max>> acc;
	acc(2);
	acc(-1);
	acc(1);
	//This displays "(-1, 2)"
	std::cout << "(" << min(acc) << "; " << max(acc) << ")" << std::endl;
}

///Passing Optional Parameters
void Passing_Optional_Parameters_test()
{
	// Define a feature for tracking covariate data
	typedef tag::tail_variate< int, tag::covariate1, left > my_tail_variate_tag;

	// This will calculate the left tail and my_tail_variate_tag for N == 2
	// using the tag::tail<left>::cache_size named parameter
	accumulator_set< double, features< my_tail_variate_tag > > acc(
		tag::tail<left>::cache_size = 2);

	// push in some samples and some covariates by using 
	// the covariate1 named parameter
	acc(1.2, covariate1 = 12);
	acc(2.3, covariate1 = -23);
	acc(3.4, covariate1 = 34);
	acc(4.5, covariate1 = -45);

	// Define an extractor for the my_tail_variate_tag feature
	extractor< my_tail_variate_tag > my_tail_variate;

	// Write the tail statistic to std::cout. This will print "4.5, 3.4, "
	std::ostream_iterator< double > dout(std::cout, ", ");
	std::copy(tail(acc).begin(), tail(acc).end(), dout);

	// Write the tail_variate statistic to std::cout. This will print "-45, 34, "
	std::ostream_iterator< int > iout(std::cout, ", ");
	std::copy(my_tail_variate(acc).begin(), my_tail_variate(acc).end(), iout);
}

void accumulator_set_weight_sum()
{
	// Since we specified a weight, tag::sum becomes tag::weighted_sum
	accumulator_set< int, features< tag::weighted_sum >, int > acc;
	acc(1, weight = 2); //   1 * 2
	acc(2, weight = 4); //   2 * 4
	acc(3, weight = 6); // + 3 * 6
	// This prints "28"
	std::cout << sum(acc) << std::endl;
}

int main()
{
	accumulator_set_weight_sum();
	system("pause");
}