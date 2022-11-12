#include "utility.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include "vector.hpp"

#define _is_integral	ft::is_integral
#define _enable_if		ft::enable_if
#define _lexicographical ft::lexicographical_compare
#define _vector			 ft::vector

volatile static time_t g_start1;
volatile static time_t g_start2;
volatile static time_t g_end1;
volatile static time_t g_end2;

int _ratio = 10000;

const std::string GREEN = "\x1B[1;32m";
const std::string REDD = "\x1B[1;31m";
const std::string YELLOW = "\x1B[1;33m";
const std::string WHITE = "\x1B[1;39m";
const std::string RESET = "\033[0m";

time_t timer() {
	struct timeval start = {};
	gettimeofday(&start, nullptr);
	time_t msecs_time = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	return msecs_time;
}

void printElement(std::string t) {
	if (t == "OK")
	    t = GREEN + t + RESET;
	else if (t == "FAILED") t = REDD + t + RESET;
	std::cout << std::left << std::setw(30) << std::setfill(' ') << t;
}

int run_bool_unit_test(std::string test_name, bool (func1)()) {
    int ret = 0;
    time_t t1;
    time_t t2;
    bool res;

	printElement(test_name);
	res = func1();
	if (res) {
	    printElement("OK");
	    ret = 0;
	}
	else {
	    printElement("FAILED");
	    ret = 1;
	}
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	std::cout << std::endl;

    return ret;
}

bool is_integral_test_() {
	std::vector<int> v;
	bool res = 1;
	g_start2 = timer(); g_end2 = timer(); g_start1 = timer(); g_end1 = timer();
	(_is_integral<float>() == std::is_integral<float>()) ? 0 : res = 0;
	(_is_integral<int>() == std::is_integral<int>()) ? 0 : res = 0;
	(_is_integral<bool>() == std::is_integral<bool>()) ? 0 : res = 0;
	(_is_integral<char>() == std::is_integral<char>()) ? 0 : res = 0;
	(_is_integral<signed char>() == std::is_integral<signed char>()) ? 0 : res = 0;
	(_is_integral<unsigned char>() == std::is_integral<unsigned char>()) ? 0 : res = 0;
	(_is_integral<wchar_t>() == std::is_integral<wchar_t>()) ? 0 : res = 0;
	(_is_integral<char16_t>() == std::is_integral<char16_t>()) ? 0 : res = 0;
	(_is_integral<short>() == std::is_integral<short>()) ? 0 : res = 0;
	(_is_integral<unsigned short>() == std::is_integral<unsigned short>()) ? 0 : res = 0;
	(_is_integral<unsigned int>() == std::is_integral<unsigned int>()) ? 0 : res = 0;
	(_is_integral<long>() == std::is_integral<long>()) ? 0 : res = 0;
	(_is_integral<unsigned long>() == std::is_integral<unsigned long>()) ? 0 : res = 0;
	(_is_integral<long long>() == std::is_integral<long long>()) ? 0 : res = 0;
	(_is_integral<unsigned long long>() == std::is_integral<unsigned long long>()) ? 0 : res = 0;
	return res;
}

template <class T> typename _enable_if< std::is_unsigned<T>::value >::type
		foo(T) {
	g_start1 = -20;
}

template <class T> typename _enable_if< std::is_signed<T>::value >::type
		foo(T) {
	g_start2 = -20;
}

bool enable_if_test_() {
	std::vector<int> v;
	bool res = 1;
	unsigned int xx = 5;
	int x = 5;
	foo(xx);
	foo(x);
	if (g_start1 != -20 && g_start2 != -20)
		res = 0;
	g_start2 = timer(); g_end2 = timer(); g_start1 = timer(); g_end1 = timer();
	return res;
}

bool lexicographical_test() {
	std::vector<int> result, result2;
	std::vector<char> v1, v2;
	std::vector<char> b1, b2;
	v1.assign(5000 * _ratio, 'f');
	v1.push_back('e');
	v2.assign(5000 * _ratio, 'f');
	v2.push_back('e');
	b1.assign(5000 * _ratio, 'f');
	b1.push_back('e');
	b2.assign(5000 * _ratio, 'f');
	b2.push_back('e');
	g_start1 = timer();
	result.push_back(std::lexicographical_compare(v1.begin(), v1.end(), v2.begin(), v2.end()));
	g_end1 = timer();
	g_start2 = timer();
	result2.push_back(_lexicographical(b1.begin(), b1.end(), b2.begin(), b2.end()));
	g_end2 = timer();
	return result == result2;
}

void	printVectors(std::vector<std::string> uno, std::vector<std::string> due)
{
	std::vector<std::string>::iterator	unoIter;
	std::vector<std::string>::iterator	dueIter;

	unoIter = uno.begin();
	dueIter = due.begin();
	while (unoIter != uno.end())
		std::cout << *unoIter++ << "   " << *dueIter++ << std::endl;
}

bool iterator_traits_test() {
	std::vector<std::string> res;
	std::vector<std::string> res2;
	g_start1 = g_end1 = timer();

	res.push_back(typeid(std::vector<int>::iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::iterator::iterator_type).name());
	res.push_back(typeid(std::vector<int>::iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::iterator::reference).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::iterator_category).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::value_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::difference_type).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::pointer).name());
	res.push_back(typeid(std::vector<int>::reverse_iterator::reference).name());

	res2.push_back(typeid(_vector<int>::iterator::iterator_category).name());
	res2.push_back(typeid(_vector<int>::iterator::value_type).name());
	res2.push_back(typeid(_vector<int>::iterator::difference_type).name());
	std::cout << typeid(_vector<int>::iterator::iterator_type).name() << std::endl;
	res2.push_back(typeid(_vector<int>::iterator::iterator_type).name());
	res2.push_back(typeid(_vector<int>::iterator::pointer).name());
	res2.push_back(typeid(_vector<int>::iterator::reference).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::iterator_category).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::value_type).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::difference_type).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::pointer).name());
	res2.push_back(typeid(_vector<int>::reverse_iterator::reference).name());

	std::cout << std::endl;
	printVectors(res, res2);
	return res == res2;
}

int main() {

	exit(run_bool_unit_test("iterators_traits", iterator_traits_test));
}
