#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include <set>
#include "set.hpp"

#define _set	ft::set
#define _pair	ft::pair
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
		while (iter != res1.end())
			std::cout << "TESTER: " << *iter++ << " NOSTRO: " << *iter2++ << std::endl;
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

template <class T>
std::vector<int> insert_test(std::set<T> st) {
    std::vector<int> v;
    std::pair<std::set<int>::iterator , bool> pair = st.insert(7);
    std::set<int>::iterator it = st.begin();
    v.push_back(*it);

    v.push_back(*(pair.first));
    v.push_back(pair.second);
    st.insert(9);
    std::pair<std::set<int>::iterator , bool> pair2 = st.insert(9);
    std::set<int>::iterator it2 = pair.first;
    v.push_back(*it2);
    v.push_back(*(pair2.first));
    v.push_back(pair2.second);
    g_start1 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(i);
    }
    g_end1 = timer();
    typename std::set<T>::iterator it3 = st.begin();
    for (; it3 != st.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(st.size());
	std::cout << "SIZE " << st.size() << std::endl;
    return v;
}

template <class T>
std::vector<int> insert_test(_set<T> st) {
    std::vector<int> v;
    _pair<_set<int>::iterator , bool> pair = st.insert(7);
    _set<int>::iterator it = st.begin();
    v.push_back(*it);

    v.push_back(*(pair.first));
    v.push_back(pair.second);
    st.insert(9);
    _pair<_set<int>::iterator , bool> pair2 = st.insert(9);
    _set<int>::iterator it2 = pair.first;
    v.push_back(*it2);
    v.push_back(*(pair2.first));
    v.push_back(pair2.second);
    g_start2 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(i);
    }
    g_end2 = timer();

    typename _set<T>::iterator it3 = st.begin();
    for (; it3 != st.end(); ++it3) {
        v.push_back(*it3);
    }
    v.push_back(st.size());
	std::cout << "SIZE " << st.size() << std::endl;
    return v;
}

template <class T>
std::vector<int> reverse_iterators_test(std::set<T> st) {
    std::vector<int> v;

    g_start1 = g_end1 = timer();
    st.insert(5);
    st.insert(3);
    st.insert(7);
    typename std::set<T>::reverse_iterator rit = st.rbegin();
    typename std::set<T>::reverse_iterator rit2 = st.rend();
    v.push_back(*rit);
    rit++;
    rit2--;
    v.push_back(*rit);
    v.push_back(*rit2);
    rit++;
    v.push_back(*rit == *rit2);
    v.push_back(rit == rit2);
    rit2--;
    v.push_back(*rit);
    v.push_back(*rit2);
    v.push_back(*rit2 > *rit);
    v.push_back(*rit2 < *rit);
    v.push_back(*(--rit));
    v.push_back(*(++rit2));
    v.push_back(*(rit--));
    v.push_back(*(rit2++));
    return v;
}

template <class T>
std::vector<int> reverse_iterators_test(_set<T> st) {

    std::vector<int> v;

    g_start2 = g_end2 = timer();
    st.insert(5);
    st.insert(3);
    st.insert(7);
    typename _set<T>::reverse_iterator rit = st.rbegin();
    typename _set<T>::reverse_iterator rit2 = st.rend();
    v.push_back(*rit);
    rit++;
    rit2--;
    v.push_back(*rit);
    v.push_back(*rit2);
    rit++;
    v.push_back(*rit == *rit2);
    v.push_back(rit == rit2);
    rit2--;
    v.push_back(*rit);
    v.push_back(*rit2);
    v.push_back(*rit2 > *rit);
    v.push_back(*rit2 < *rit);
    v.push_back(*(--rit));
    v.push_back(*(++rit2));
    v.push_back(*(rit--));
    v.push_back(*(rit2++));
    return v;
}

template <class T>
std::vector<int> clear_test(std::set<T> st) {
    std::vector<int> v;
    st.clear();
    for (int i = 0; i < 25 * _ratio; ++i)
        st.insert(i);
    v.push_back(st.size());
    g_start1 = timer();
    st.clear();
    g_end1 = timer();
    v.push_back(st.size());
    typename std::set<T>::iterator it = st.begin();
    if (it == st.end())
        v.push_back(1);
    return v;
}

template <class T>
std::vector<int> clear_test(_set<T> st) {
    std::vector<int> v;
    st.clear();
    for (int i = 0; i < 25 * _ratio; ++i)
        st.insert(i);
    v.push_back(st.size());
    g_start2 = timer();
    st.clear();
    g_end2 = timer();
    v.push_back(st.size());
    typename _set<T>::iterator it = st.begin();
    if (it == st.end())
        v.push_back(1);
    return v;
}

template <class T>
std::vector<int> insert_test_3(std::set<T> st) {
    std::vector<int> v;
    typename std::set<T>::iterator it = st.end();
    g_start1 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(it, i);
    }
    g_end1 = timer();
    typename std::set<T>::iterator it2 = st.begin();
    for (; it2 != st.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int> insert_test_3(_set<T> st) {
    std::vector<int> v;
    typename _set<T>::iterator it = st.end();
    g_start2 = timer();
    for (int i = 0; i < 50 * _ratio; ++i) {
        st.insert(it, i);
    }
    g_end2 = timer();
    typename _set<T>::iterator it2 = st.begin();
    for (; it2 != st.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int> erase_test_1(std::set<T> st) {
    std::vector<int> v;
    v.push_back(st.erase(3));
    for (int i = 0; i < 30 * _ratio; ++i)
        st.insert(i);
    typename std::set<T>::iterator it = st.begin();
    v.push_back(*it);
    v.push_back(st.erase(-5));
    v.push_back(st.size());
    v.push_back(st.erase(0));
    v.push_back(st.size());
    typename std::set<T>::iterator it4 = st.begin();
    g_start1 = timer();
    for (; it4 != st.end(); it4 = st.begin())
        st.erase(*it4);
    g_end1 = timer();
    v.push_back(st.erase(30 * _ratio - 1));
    v.push_back(st.size());
    std::set<int> st2;
    for (int i = 0; i < 10 ; ++i)
        st2.insert(i);
    st2.erase(2);
    st2.erase(7);
    typename std::set<T>::iterator it3 = st2.begin();
    for (; it3 != st2.end(); ++it3) {
        v.push_back(*it3);
    }
    return v;
}

template <class T>
std::vector<int> erase_test_1(_set<T> st) {
    std::vector<int> v;
    v.push_back(st.erase(3));
    for (int i = 0; i < 30 * _ratio; ++i)
        st.insert(i);
    typename _set<T>::iterator it = st.begin();
    v.push_back(*it);
    v.push_back(st.erase(-5));
    v.push_back(st.size());
    v.push_back(st.erase(0));
    v.push_back(st.size());
    typename _set<T>::iterator it4 = st.begin();
    g_start2 = timer();
    for (; it4 != st.end(); it4 = st.begin())
        st.erase(*it4);
    g_end2 = timer();
    v.push_back(st.erase(30 * _ratio - 1));
    v.push_back(st.size());
    _set<int> st2;
    for (int i = 0; i < 10 ; ++i)
        st2.insert(i);
    st2.erase(2);
    st2.erase(7);
    typename _set<T>::iterator it3 = st2.begin();
    for (; it3 != st2.end(); ++it3) {
        v.push_back(*it3);
    }
    return v;
}

template <class T>
std::vector<int> insert_test_2(std::set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    std::set<int> st2;
    g_start1 = timer();
    st2.insert(st.begin(), st.end());
    g_end1 = timer();
    typename std::set<T>::iterator it2 = st2.begin();
    for (; it2 != st2.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int> insert_test_2(_set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    _set<int> st2;
    g_start2 = timer();
    st2.insert(st.begin(), st.end());
    g_end2 = timer();
    typename _set<T>::iterator it2 = st2.begin();
    for (; it2 != st2.end(); ++it2) {
        v.push_back(*it2);
    }
    return v;
}

template <class T>
std::vector<int> erase_test_3(std::set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    g_start1 = timer();
    st.erase(st.begin(), --st.end());
    g_end1 = timer();
    v.push_back(*(st.begin()));
    return v;
}

template <class T>
std::vector<int> erase_test_3(_set<T> st) {
    std::vector<int> v;
    for (int i = 0; i < 50 * _ratio; ++i)
        st.insert(i);
    g_start2 = timer();
    st.erase(st.begin(), --st.end());
    g_end2 = timer();
    v.push_back(*(st.begin()));
    return v;
}

template <class T>
std::vector<int> count_test(std::set<T> st) {
    std::vector<int> v;
    g_start1 = g_end1 = timer();
    v.push_back(st.count(0));
    st.insert(0);
    v.push_back(st.count(0));
    return v;
}

template <class T>
std::vector<int> count_test(_set<T> st) {
    std::vector<int> v;
    g_start2 = g_end2 = timer();
    v.push_back(st.count(0));
    st.insert(0);
    v.push_back(st.count(0));
    return v;
}

template <class T>
std::vector<int> lower_bound_test(std::set<T> st) {
    std::vector<int> v;
    std::set<int, std::greater<int> > st2;
    st.insert(10);
    st2.insert(10);
    if (st.lower_bound(11) == st.end())
        v.push_back(1);
    if (st2.lower_bound(1) == st2.end())
        v.push_back(1);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);
    st.insert(60);
    st2.insert(20);
    st2.insert(30);
    st2.insert(40);
    st2.insert(50);
    st2.insert(60);
    std::set<int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = st.lower_bound(i);
        v.push_back(*it);
    }
    for (int i = 11; i < 70; i += 10) {
        it = st2.lower_bound(i);
        v.push_back(*it);
    }
    std::set<int> st3;
    for (int i = 0; i < 50 * _ratio; ++i) {
        st3.insert(i);
    }
    g_start1 = timer();
    st3.lower_bound(49 * _ratio);
    g_end1 = timer();
    return v;
}

template <class T>
std::vector<int> lower_bound_test(_set<T> st) {
    std::vector<int> v;
    _set<int, std::greater<int> > st2;
    st.insert(10);
    st2.insert(10);
    if (st.lower_bound(11) == st.end())
        v.push_back(1);
    if (st2.lower_bound(1) == st2.end())
        v.push_back(1);
    st.insert(20);
    st.insert(30);
    st.insert(40);
    st.insert(50);
    st.insert(60);
    st2.insert(20);
    st2.insert(30);
    st2.insert(40);
    st2.insert(50);
    st2.insert(60);
    _set<int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = st.lower_bound(i);
        v.push_back(*it);
    }
    for (int i = 11; i < 70; i += 10) {
        it = st2.lower_bound(i);
        v.push_back(*it);
    }
    _set<int> st3;
    for (int i = 0; i < 50 * _ratio; ++i) {
        st3.insert(i);
    }
    g_start2 = timer();
    st3.lower_bound(49 * _ratio);
    g_end2 = timer();
    return v;
}

int main() {

    exit(run_set_unit_test<int>("lower_bound()", lower_bound_test, lower_bound_test));
}
