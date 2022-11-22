#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include <set>
#include "set.hpp"

#define _set	ft::set
const std::string GREEN = "\x1B[1;32m";
const std::string REDD = "\x1B[1;31m";
const std::string YELLOW = "\x1B[1;33m";
const std::string WHITE = "\x1B[1;39m";
const std::string RESET = "\033[0m";

volatile static time_t g_start1;
volatile static time_t g_start2;
volatile static time_t g_end1;
volatile static time_t g_end2;

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


int _ratio = 10000;

template <class T>
int run_set_unit_test(std::string test_name, std::vector<int> (func1)(std::set<T>), std::vector<int> (func2)(_set<T>)) {
    int    result;
    int    leaks;
    time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::set<int> set;
	_set<int> my_set;

	printElement(test_name);
	res1 = func1(set);
	res2 = func2(my_set);
	if (res1 == res2) {
	    printElement("OK");
	    result = 0;
	}
	else {
		std::cout << std::endl;
		std::vector<int>::iterator	iter = res1.begin();
		std::vector<int>::iterator		iter2 = res2.begin();
		while (iter != res1.begin() + 10)
		{
			std::cout << "TESTER: " << *iter++ << " NOSTRO: " << *iter2++ <<  std::endl;
		}
	    printElement("FAILED");
	    result = 1;
	}
	t1 = g_end1 - g_start1, t2 = g_end2 - g_start2;
	(t1 >= t2) ? printElement(GREEN + std::to_string(t2) + "ms" + RESET) : printElement(REDD + std::to_string(t2) + "ms" + RESET);
	(t1 > t2) ? printElement(REDD + std::to_string(t1) + "ms" + RESET) : printElement(GREEN + std::to_string(t1) + "ms" + RESET);
	// leaks = leaks_test(getpid());
	leaks = 0;
	std::cout << std::endl;

	return !(!result && !leaks);
}

template <class T>
std::vector<int> copy_constructor_test(std::set<T> st) {
    std::vector<int> v;

    for (int i = 0; i < 30 * _ratio; ++i) {
        st.insert(i);
    }
    g_start1 = timer();
    std::set<int> st2(st.begin(), st.end());
    g_end1 = timer();
    std::set<int>::iterator it = st2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(*it);
    }
    return v;
}

template <class T>
std::vector<int> copy_constructor_test(_set<T> st) {
    std::vector<int> v;

    for (int i = 0; i < 30 * _ratio; ++i)
        st.insert(i);
    g_start2 = timer();
    _set<int> st2(st.begin(), st.end());
    g_end2 = timer();
    _set<int>::iterator it = st2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(*it);
    }
    return v;
}

template <class T, class C>
void fillSet(std::set<T, C> &mp) {
	mp.insert(16);
	mp.insert(8);
	mp.insert(23);
	mp.insert(7);
	mp.insert(19);
	mp.insert(29);
	mp.insert(41);
	mp.insert(4);
	mp.insert(11);
}

template <class T, class C>
void fillSet(_set<T, C> &mp) {
	mp.insert(16);
	mp.insert(8);
	mp.insert(23);
	mp.insert(7);
	mp.insert(19);
	mp.insert(29);
	mp.insert(41);
	mp.insert(4);
	mp.insert(11);
}

template <class T>
std::vector<int>    iterators_test(std::set<T> st) {
    std::vector<int> v;
    std::set<T> stt;
    fillSet(stt);
    for (typename std::set<T>::iterator it = stt.begin(); it != stt.end(); it++) { v.push_back(*it); }
    for (typename std::set<T>::iterator it = --stt.end(); it != stt.begin(); it--) { v.push_back(*it); }
    std::set<int> mp0;
    std::set<int>::iterator ii = mp0.insert(3).first;
    ii++;
    v.push_back(*(--ii));
    for (int i = 0; i < 5; ++i)
        st.insert(i);
    typename std::set<T>::iterator it = st.begin();
    typename std::set<T>::iterator it2 = st.end();
    g_start1 = timer();
    v.push_back(*it);
    it++;
    it++;
    it++;
    it++;
    v.push_back(*it);
    it++;
    it--;
    v.push_back(*it);
    it2--;
    v.push_back(*it2);
    v.push_back(it2 == it);
    v.push_back(*(--it2));
    v.push_back(*(it2--));
    v.push_back(*(it2++));
    v.push_back(*(++it2));
    g_end1 = timer();
    return v;
}

template <class T>
std::vector<int> iterators_test(_set<T> st) {
    std::vector<int> v;
    _set<T> stt;
    fillSet(stt);
	typename _set<T>::iterator iterrr = stt.begin();
    for (typename _set<T>::iterator it = stt.begin(); it != stt.end(); it++)
	{ v.push_back(*it); }
    for (typename _set<T>::iterator it = --stt.end(); it != stt.begin(); it--) 
	{ v.push_back(*it); }
    _set<int> mp0;
    _set<int>::iterator ii = mp0.insert(3).first;
    ii++;
    v.push_back(*(--ii));
    for (int i = 0; i < 5; ++i)
        st.insert(i);
    typename _set<T>::iterator it = st.begin();
    typename _set<T>::iterator it2 = st.end();
    g_start2 = timer();
    v.push_back(*it);
    it++;
    it++;
    it++;
    it++;
    v.push_back(*it);
    it++;
    it--;
    v.push_back(*it);
    it2--;
    v.push_back(*it2);
    v.push_back(it2 == it);
    v.push_back(*(--it2));
    v.push_back(*(it2--));
    v.push_back(*(it2++));
    v.push_back(*(++it2));
    g_end2 = timer();
    return v;
}

int main() {

    exit(run_set_unit_test<int>("iterators", iterators_test, iterators_test));
}