#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>
#include <map>
#include "map.hpp"
int _allocator_used = 0;
// #include "Alloc.hpp"

#define _map	ft::map
#define _pair	ft::pair
#define _make_pair	ft::make_pair
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


template <class T, class V, class C>
void fillMap(std::map<T, V, C> &mp) {
	mp.insert(std::make_pair(16, 3));
	mp.insert(std::make_pair(8, 3));
	mp.insert(std::make_pair(23, 3));
	mp.insert(std::make_pair(7, 3));
	mp.insert(std::make_pair(19, 3));
	mp.insert(std::make_pair(29, 3));
	mp.insert(std::make_pair(41, 3));
	mp.insert(std::make_pair(4, 3));
	mp.insert(std::make_pair(11, 3));
}

template <class T, class V, class C>
void fillMap(_map<T, V, C> &mp) {
	mp.insert(_make_pair(16, 3));
	mp.insert(_make_pair(8, 3));
	mp.insert(_make_pair(23, 3));
	mp.insert(_make_pair(7, 3));
	mp.insert(_make_pair(19, 3));
	mp.insert(_make_pair(29, 3));
	mp.insert(_make_pair(41, 3));
	mp.insert(_make_pair(4, 3));
	mp.insert(_make_pair(11, 3));
}

class MapBoolTest {
public:
	std::map<int, int> m1, m2, m3, m4;
	std::map<std::string, std::string> m5, m6, m7, m8, m9;
	_map<int, int> mp1, mp2, mp3, mp4;
	_map<std::string, std::string> mp5, mp6, mp7, mp8, mp9;

	MapBoolTest() {
		m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
		m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
		m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
		m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
		m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
		m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
		m6.insert(std::make_pair("123", "124")); mp6.insert(ft::make_pair("123", "124"));
		m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
		m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
		m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
	}
};


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


template <class T, class V>
int run_map_unit_test(std::string test_name, std::vector<int> (func1)(std::map<T, V>), std::vector<int> (func2)(_map<T, V>)) {
    int    result;
    int    leaks;
	time_t t1;
	time_t t2;
	std::vector<int > res1;
	std::vector<int > res2;
	std::map<int, int> map;
	_map<int, int> my_map;

	printElement(test_name);
	res1 = func1(map);
	res2 = func2(my_map);
	if (res1 == res2) {
	    printElement("OK");
	    result = 0;
	}
	else {
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

template <class T, class V, class C, class A>
int run_map_allocator_unit_test(std::string test_name, void (func)(_map<T, V, C, A>)) {

    _map<T, V, C, A> my_map;

    printElement(test_name);
    func(my_map);
    if (_allocator_used) {
        printElement("OK");
        std::cout << std::endl;
        return (0);
    }
    else {
        printElement("FAILED");
        std::cout << std::endl;
        return (1);
    }
}


template <class T, class V>
std::vector<int> copy_constructor_test(std::map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    g_start1 = timer();
    std::map<int, int> mp2(mp.begin(), mp.end());
    g_end1 = timer();
    std::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> copy_constructor_test(_map<T, V> mp) {

    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    g_start2 = timer();
    _map<int, int> mp2(mp.begin(), mp.end());
    g_end2 = timer();
    _map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 * _ratio; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    std::map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(std::make_pair(i, j));
    g_start1 = timer();
    mp2 = mp;
    g_end1 = timer();
    typename std::map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

template <class T, class V>
std::vector<int> assign_overload_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    _map<T, V> mp2;
    for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
        mp2.insert(_make_pair(i, j));
    g_start2 = timer();
    mp2 = mp;
    g_end2 = timer();
    typename _map<T, V>::iterator it = mp2.begin();
    for (; it != mp2.end(); it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    v.push_back(mp2.size());
    return v;
}

template <class T, class V>
std::vector<int> comparator_test(std::map<T, V> mp) {

    std::vector<int> v;
    fillMap(mp);
    for (typename std::map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::greater<int> > mp1;
    fillMap(mp1);
    v.push_back(mp1.begin()->first);
    mp1.erase(41);
    v.push_back(mp1.begin()->first);
    mp1.erase(29);
    v.push_back(mp1.begin()->first);
    std::map<int, int, std::greater<int> > mp2;
    mp2.insert(std::make_pair(3, 3));
    v.push_back(mp2.begin()->first);
    mp2.erase(3);
    if (mp2.begin() == mp2.end())
        v.push_back(1);
    std::map<int, int, std::plus<int> > mp3;
    fillMap(mp3);
    for (typename std::map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::minus<int> > mp4;
    fillMap(mp4);
    for (typename std::map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::greater_equal<int> > mp5;
    fillMap(mp5);
    for (typename std::map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::multiplies<int> > mp6;
    fillMap(mp6);
    for (typename std::map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::bit_xor<int> > mp7;
    fillMap(mp7);
    for (typename std::map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::logical_and<int> > mp8;
    fillMap(mp8);
    for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
    g_start1 = timer();
    g_end1 = timer();
    v.push_back(mp1.size());
    return v;
}

template <class T, class V>
std::vector<int> comparator_test(_map<T, V> mp) {
    std::vector<int> v;
    fillMap(mp);
    for (typename _map<T, V>::iterator it = mp.begin(); it != mp.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp.end(); it != mp.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::greater<int> > mp1;
    fillMap(mp1);
    v.push_back(mp1.begin()->first);
    mp1.erase(41);
    v.push_back(mp1.begin()->first);
    mp1.erase(29);
    v.push_back(mp1.begin()->first);
    _map<int, int, std::greater<int> > mp2;
    mp2.insert(_make_pair(3, 3));
    v.push_back(mp2.begin()->first);
    mp2.erase(3);
    if (mp2.begin() == mp2.end())
        v.push_back(1);
    _map<int, int, std::plus<int> > mp3;
    fillMap(mp3);
    for (typename _map<T, V>::iterator it = mp3.begin(); it != mp3.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp3.end(); it != mp3.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::minus<int> > mp4;
    fillMap(mp4);
    for (typename _map<T, V>::iterator it = mp4.begin(); it != mp4.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp4.end(); it != mp4.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::greater_equal<int> > mp5;
    fillMap(mp5);
    for (typename _map<T, V>::iterator it = mp5.begin(); it != mp5.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp5.end(); it != mp5.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::multiplies<int> > mp6;
    fillMap(mp6);
    for (typename _map<T, V>::iterator it = mp6.begin(); it != mp6.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp6.end(); it != mp6.begin(); it--) { v.push_back(it->first); }
    _map<int, int, std::bit_xor<int> > mp7;
    fillMap(mp7);
    for (typename _map<T, V>::iterator it = mp7.begin(); it != mp7.end(); it++) { v.push_back(it->first); }
    for (typename _map<T, V>::iterator it = --mp7.end(); it != mp7.begin(); it--) { v.push_back(it->first); }
    std::map<int, int, std::logical_and<int> > mp8;
    fillMap(mp8);
    for (typename std::map<T, V>::iterator it = mp8.begin(); it != mp8.end(); it++) { v.push_back(it->first); }
    for (typename std::map<T, V>::iterator it = --mp8.end(); it != mp8.begin(); it--) { v.push_back(it->first); }
    g_start1 = timer();
    g_end1 = timer();
    v.push_back(mp1.size());

    return v;
}

template <class T, class V>
std::vector<int> at_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 70 * _ratio; ++i, ++j)
        mp.insert(std::make_pair(i, j));
    g_start1 = timer();
    try {
        v.push_back(mp.at(40 * _ratio));
        v.push_back(mp.at(40 * _ratio + 1));
    } catch (std::exception &e) {
        v.push_back(1);
    }
    g_end1 = timer();
    return v;
}

template <class T, class V>
std::vector<int> at_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = 0, j = 10; i < 70 * _ratio; ++i, ++j)
        mp.insert(_make_pair(i, j));
    g_start2 = timer();
    try {
        v.push_back(mp.at(40 * _ratio));
        v.push_back(mp.at(40 * _ratio + 1));
    } catch (std::exception &e) {
        v.push_back(1);
    }
    g_end2 = timer();
    return v;
}

template <class T, class V>
        std::vector<int> operator_sq_test(std::map<T, V> mp) {
    std::vector<int> v;
    mp.insert(std::make_pair(3, 3));
    typename std::map<T, V>::iterator it = mp.begin();
    g_start1 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    mp[3] = 10;
    v.push_back(it->first);
    v.push_back(it->second);
    mp[2] = 9;
    it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    it++;
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(mp.size());
    g_end1 = timer();
    return v;
}

template <class T, class V>
        std::vector<int> operator_sq_test(_map<T, V> mp) {
    std::vector<int> v;
    mp.insert(_make_pair(3, 3));
    typename _map<T, V>::iterator it = mp.begin();
    g_start2 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    mp[3] = 10;
    v.push_back(it->first);
    v.push_back(it->second);
    mp[2] = 9;
    it = mp.begin();
    v.push_back(it->first);
    v.push_back(it->second);
    it++;
    v.push_back(it->first);
    v.push_back(it->second);
    v.push_back(mp.size());
    g_end2 = timer();
    return v;
}

template <class T, class V>
std::vector<int> count_test(std::map<T, V> mp) {
    std::vector<int> v;
    g_start1 = g_end1 = timer();
    v.push_back(mp.count(0));
    mp.insert(std::make_pair(0, 0));
    v.push_back(mp.count(0));
    return v;
}

template <class T, class V>
std::vector<int> count_test(_map<T, V> mp) {
    std::vector<int> v;
    g_start2 = g_end2 = timer();
    v.push_back(mp.count(0));
    mp.insert(_make_pair(0, 0));
    v.push_back(mp.count(0));
    return v;
}

template <class T, class V>
std::vector<int> find_test(std::map<T, V> mp) {
    std::vector<int> v;
    for (int i = -75 * _ratio, j = 0; i < 75 * _ratio; ++i, ++j) {
        mp.insert(std::make_pair(i, j));
    }
    g_start1 = timer();
    typename std::map<T, V>::iterator it = mp.find(34 * _ratio);
    g_end1 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-34 * _ratio);
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-75 * _ratio);
    if (it == mp.end())
        v.push_back(1);
    return v;
}

template <class T, class V>
std::vector<int> find_test(_map<T, V> mp) {
    std::vector<int> v;
    for (int i = -75 * _ratio, j = 0; i < 75 * _ratio; ++i, ++j) {
        mp.insert(_make_pair(i, j));
    }
    g_start2 = timer();
    typename _map<T, V>::iterator it = mp.find(34 * _ratio);
    g_end2 = timer();
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-34 * _ratio);
    v.push_back(it->first);
    v.push_back(it->second);
    it = mp.find(-75 * _ratio);
    if (it == mp.end())
        v.push_back(1);
    return v;
}

template <class T, class V>
std::vector<int> lower_bound_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::map<int, int, std::greater<int> > mp2;
    mp.insert(std::make_pair(10, 10));
    mp2.insert(std::make_pair(10, 10));
    if (mp.lower_bound(11) == mp.end())
        v.push_back(1);
    if (mp2.lower_bound(1) == mp2.end())
        v.push_back(1);
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    mp2.insert(std::make_pair(20, 20));
    mp2.insert(std::make_pair(30, 30));
    mp2.insert(std::make_pair(40, 40));
    mp2.insert(std::make_pair(50, 50));
    mp2.insert(std::make_pair(60, 60));
    std::map<int, int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = mp.lower_bound(i);
        v.push_back(it->first);
    }
    for (int i = 11; i < 70; i += 10) {
        it = mp2.lower_bound(i);
        v.push_back(it->first);
    }
    std::map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp3.insert(std::make_pair(i, j));
    }
    g_start1 = timer();
    mp3.lower_bound(49 * _ratio);
    g_end1 = timer();
    return v;
}

template <class T, class V>
std::vector<int> lower_bound_test(_map<T, V> mp) {
    std::vector<int> v;
    _map<int, int, std::greater<int> > mp2;
    mp.insert(_make_pair(10, 10));
    mp2.insert(_make_pair(10, 10));
    if (mp.lower_bound(11) == mp.end())
        v.push_back(1);
    if (mp2.lower_bound(1) == mp2.end())
        v.push_back(1);
    mp.insert(_make_pair(20, 20));
    mp.insert(_make_pair(30, 30));
    mp.insert(_make_pair(40, 40));
    mp.insert(_make_pair(50, 50));
    mp.insert(_make_pair(60, 60));
    mp2.insert(_make_pair(20, 20));
    mp2.insert(_make_pair(30, 30));
    mp2.insert(_make_pair(40, 40));
    mp2.insert(_make_pair(50, 50));
    mp2.insert(_make_pair(60, 60));
    _map<int, int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = mp.lower_bound(i);
        v.push_back(it->first);
    }
    for (int i = 11; i < 70; i += 10) {
        it = mp2.lower_bound(i);
        v.push_back(it->first);
    }
    _map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp3.insert(_make_pair(i, j));
    }
    g_start2 = timer();
    mp3.lower_bound(49 *_ratio);
    g_end2 = timer();
    return v;
}

template <class T, class V>
        std::vector<int> upper_bound_test(std::map<T, V> mp) {
    std::vector<int> v;
    std::map<int, int, std::greater<int> > mp2;
    mp.insert(std::make_pair(10, 10));
    mp2.insert(std::make_pair(10, 10));
    if (mp.upper_bound(11) == mp.end())
        v.push_back(1);
    if (mp2.upper_bound(1) == mp2.end())
        v.push_back(1);
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    mp2.insert(std::make_pair(20, 20));
    mp2.insert(std::make_pair(30, 30));
    mp2.insert(std::make_pair(40, 40));
    mp2.insert(std::make_pair(50, 50));
    mp2.insert(std::make_pair(60, 60));
    std::map<int, int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = mp.upper_bound(i);
        v.push_back(it->first);
    }
    for (int i = 11; i < 70; i += 10) {
        it = mp2.upper_bound(i);
        v.push_back(it->first);
    }
    std::map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp3.insert(std::make_pair(i, j));
    }
    std::map<int, int> mp4;
    mp.insert(std::make_pair(-10, 10));
    mp.insert(std::make_pair(-20, 20));
    v.push_back((--mp.upper_bound(0))->first);
    g_start1 = timer();
    mp3.upper_bound(49 * _ratio);
    g_end1 = timer();
    return v;
}

template <class T, class V>
        std::vector<int> upper_bound_test(_map<T, V> mp) {
    std::vector<int> v;
    _map<int, int, std::greater<int> > mp2;
    mp.insert(_make_pair(10, 10));
    mp2.insert(_make_pair(10, 10));
    if (mp.upper_bound(11) == mp.end())
        v.push_back(1);
    if (mp2.upper_bound(1) == mp2.end())
        v.push_back(1);
    mp.insert(_make_pair(20, 20));
    mp.insert(_make_pair(30, 30));
    mp.insert(_make_pair(40, 40));
    mp.insert(_make_pair(50, 50));
    mp.insert(_make_pair(60, 60));
    mp2.insert(_make_pair(20, 20));
    mp2.insert(_make_pair(30, 30));
    mp2.insert(_make_pair(40, 40));
    mp2.insert(_make_pair(50, 50));
    mp2.insert(_make_pair(60, 60));
    _map<int, int>::iterator it;
    for (int i = 1; i < 60; i += 10) {
        it = mp.upper_bound(i);
        v.push_back(it->first);
    }
    for (int i = 11; i < 70; i += 10) {
        it = mp2.upper_bound(i);
        v.push_back(it->first);
    }
    _map<int, int> mp3;
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp3.insert(_make_pair(i, j));
    }
    _map<int, int> mp4;
    mp.insert(_make_pair(-10, 10));
    mp.insert(_make_pair(-20, 20));
    v.push_back((--mp.upper_bound(0))->first);
    g_start2 = timer();
    mp3.upper_bound(49 * _ratio);
    g_end2 = timer();
    return v;
}

template <class T, class V>
std::vector<int> equal_range_test(std::map<T, V> mp) {
    std::vector<int> v;
    mp.insert(std::make_pair(10, 10));
    mp.insert(std::make_pair(20, 20));
    mp.insert(std::make_pair(30, 30));
    mp.insert(std::make_pair(40, 40));
    mp.insert(std::make_pair(50, 50));
    mp.insert(std::make_pair(60, 60));
    g_start1 = timer();
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const std::pair<std::map<int, int>::const_iterator , std::map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    g_end1 = timer();
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
    return v;
}

template <class T, class V>
std::vector<int> equal_range_test(_map<T, V> mp) {
    std::vector<int> v;
    mp.insert(_make_pair(10, 10));
    mp.insert(_make_pair(20, 20));
    mp.insert(_make_pair(30, 30));
    mp.insert(_make_pair(40, 40));
    mp.insert(_make_pair(50, 50));
    mp.insert(_make_pair(60, 60));
    g_start2 = timer();
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair = mp.equal_range(10);
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair2 = mp.equal_range(11);
    const _pair<_map<int, int>::const_iterator , _map<int, int>::const_iterator>& pair3 = mp.equal_range(1);
    g_end2 = timer();
    v.push_back(pair.first->first);
    v.push_back(pair.first->second);
    v.push_back(pair.second->first);
    v.push_back(pair.second->second);
    v.push_back(pair2.first->first);
    v.push_back(pair2.first->second);
    v.push_back(pair2.second->first);
    v.push_back(pair2.second->second);
    v.push_back(pair3.first->first);
    v.push_back(pair3.first->second);
    v.push_back(pair3.second->first);
    v.push_back(pair3.second->second);
    return v;
}

bool map_equal_test() {
	std::vector<int> result, result2;
	g_start2 = g_end2 = g_start1 = g_end1 = 0;
	MapBoolTest mt;

	result.push_back(mt.m1 == mt.m1); result.push_back(mt.m3 == mt.m3); result.push_back(mt.m5 == mt.m9);
	result.push_back(mt.m1 == mt.m2); result.push_back(mt.m3 == mt.m4); result.push_back(mt.m6 == mt.m6);
	result.push_back(mt.m1 == mt.m3); result.push_back(mt.m4 == mt.m4); result.push_back(mt.m6 == mt.m7);
	result.push_back(mt.m1 == mt.m4); result.push_back(mt.m5 == mt.m5); result.push_back(mt.m6 == mt.m8);
	result.push_back(mt.m2 == mt.m2); result.push_back(mt.m5 == mt.m6); result.push_back(mt.m6 == mt.m9);
	result.push_back(mt.m2 == mt.m3); result.push_back(mt.m5 == mt.m7); result.push_back(mt.m7 == mt.m7);
	result.push_back(mt.m2 == mt.m4); result.push_back(mt.m5 == mt.m8); result.push_back(mt.m7 == mt.m8);
	result.push_back(mt.m7 == mt.m9); result.push_back(mt.m8 == mt.m8); result.push_back(mt.m8 == mt.m9);
	result.push_back(mt.m9 == mt.m9);

	result2.push_back(mt.mp1 == mt.mp1); result2.push_back(mt.mp3 == mt.mp3); result2.push_back(mt.mp5 == mt.mp9);
	result2.push_back(mt.mp1 == mt.mp2); result2.push_back(mt.mp3 == mt.mp4); result2.push_back(mt.mp6 == mt.mp6);
	result2.push_back(mt.mp1 == mt.mp3); result2.push_back(mt.mp4 == mt.mp4); result2.push_back(mt.mp6 == mt.mp7);
	result2.push_back(mt.mp1 == mt.mp4); result2.push_back(mt.mp5 == mt.mp5); result2.push_back(mt.mp6 == mt.mp8);
	result2.push_back(mt.mp2 == mt.mp2); result2.push_back(mt.mp5 == mt.mp6); result2.push_back(mt.mp6 == mt.mp9);
	result2.push_back(mt.mp2 == mt.mp3); result2.push_back(mt.mp5 == mt.mp7); result2.push_back(mt.mp7 == mt.mp7);
	result2.push_back(mt.mp2 == mt.mp4); result2.push_back(mt.mp5 == mt.mp8); result2.push_back(mt.mp7 == mt.mp8);
	result2.push_back(mt.mp7 == mt.mp9); result2.push_back(mt.mp8 == mt.mp8); result2.push_back(mt.mp8 == mt.mp9);
	result2.push_back(mt.mp9 == mt.mp9);

	return result == result2;
}

bool map_less_than_test() {
	std::vector<int> result, result2;
	g_start2 = g_end2 = g_start1 = g_end1 = 0;
	MapBoolTest mt;

	result.push_back(mt.m1 < mt.m1); result.push_back(mt.m3 < mt.m3); result.push_back(mt.m5 < mt.m9);
	result.push_back(mt.m1 < mt.m2); result.push_back(mt.m3 < mt.m4); result.push_back(mt.m6 < mt.m6);
	result.push_back(mt.m1 < mt.m3); result.push_back(mt.m4 < mt.m4); result.push_back(mt.m6 < mt.m7);
	result.push_back(mt.m1 < mt.m4); result.push_back(mt.m5 < mt.m5); result.push_back(mt.m6 < mt.m8);
	result.push_back(mt.m2 < mt.m2);
	result.push_back(mt.m5 < mt.m6);
	result.push_back(mt.m6 < mt.m9);
	result.push_back(mt.m2 < mt.m3); result.push_back(mt.m5 < mt.m7); result.push_back(mt.m7 < mt.m7);
	result.push_back(mt.m2 < mt.m4); result.push_back(mt.m5 < mt.m8); result.push_back(mt.m7 < mt.m8);
	result.push_back(mt.m7 < mt.m9); result.push_back(mt.m8 < mt.m8); result.push_back(mt.m8 < mt.m9);
	result.push_back(mt.m9 < mt.m9);

	result2.push_back(mt.mp1 < mt.mp1); result2.push_back(mt.mp3 < mt.mp3); result2.push_back(mt.mp5 < mt.mp9);
	result2.push_back(mt.mp1 < mt.mp2); result2.push_back(mt.mp3 < mt.mp4); result2.push_back(mt.mp6 < mt.mp6);
	result2.push_back(mt.mp1 < mt.mp3); 
	result2.push_back(mt.mp4 < mt.mp4); result2.push_back(mt.mp6 < mt.mp7);
	result2.push_back(mt.mp1 < mt.mp4); result2.push_back(mt.mp5 < mt.mp5); result2.push_back(mt.mp6 < mt.mp8);
	result2.push_back(mt.mp2 < mt.mp2);
	result2.push_back(mt.mp5 < mt.mp6);
	result2.push_back(mt.mp6 < mt.mp9);
	result2.push_back(mt.mp2 < mt.mp3); result2.push_back(mt.mp5 < mt.mp7); result2.push_back(mt.mp7 < mt.mp7);
	result2.push_back(mt.mp2 < mt.mp4); result2.push_back(mt.mp5 < mt.mp8); result2.push_back(mt.mp7 < mt.mp8);
	result2.push_back(mt.mp7 < mt.mp9); result2.push_back(mt.mp8 < mt.mp8); result2.push_back(mt.mp8 < mt.mp9);
	result2.push_back(mt.mp9 < mt.mp9);

	std::cout << std::endl;

	std::vector<int>::iterator	iter = result.begin();
	std::vector<int>::iterator	iter2 = result2.begin();
	int i = 0;

	while (iter != result.end())
	{
		if (*iter != *iter2)
			std::cout << "indice: " << i << " " << *iter << std::endl;
		i++;
		iter++;
		iter2++;
	}

	return result == result2;
}

bool map_more_than_test() {
	std::vector<int> result, result2;
	g_start2 = g_end2 = g_start1 = g_end1 = 0;
	MapBoolTest mt;

	result.push_back(mt.m1 > mt.m1); result.push_back(mt.m3 > mt.m3); result.push_back(mt.m5 > mt.m9);
	result.push_back(mt.m1 > mt.m2); result.push_back(mt.m3 > mt.m4); result.push_back(mt.m6 > mt.m6);
	result.push_back(mt.m1 > mt.m3); result.push_back(mt.m4 > mt.m4); result.push_back(mt.m6 > mt.m7);
	result.push_back(mt.m1 > mt.m4); result.push_back(mt.m5 > mt.m5); result.push_back(mt.m6 > mt.m8);
	result.push_back(mt.m2 > mt.m2); result.push_back(mt.m5 > mt.m6); result.push_back(mt.m6 > mt.m9);
	result.push_back(mt.m2 > mt.m3); result.push_back(mt.m5 > mt.m7); result.push_back(mt.m7 > mt.m7);
	result.push_back(mt.m2 > mt.m4); result.push_back(mt.m5 > mt.m8); result.push_back(mt.m7 > mt.m8);
	result.push_back(mt.m7 > mt.m9); result.push_back(mt.m8 > mt.m8); result.push_back(mt.m8 > mt.m9);
	result.push_back(mt.m9 > mt.m9);

	result2.push_back(mt.mp1 > mt.mp1); result2.push_back(mt.mp3 > mt.mp3); result2.push_back(mt.mp5 > mt.mp9);
	result2.push_back(mt.mp1 > mt.mp2); result2.push_back(mt.mp3 > mt.mp4); result2.push_back(mt.mp6 > mt.mp6);
	result2.push_back(mt.mp1 > mt.mp3);
	result2.push_back(mt.mp4 > mt.mp4);
	result2.push_back(mt.mp6 > mt.mp7);
	result2.push_back(mt.mp1 > mt.mp4); result2.push_back(mt.mp5 > mt.mp5); result2.push_back(mt.mp6 > mt.mp8);
	result2.push_back(mt.mp2 > mt.mp2); result2.push_back(mt.mp5 > mt.mp6); result2.push_back(mt.mp6 > mt.mp9);
	result2.push_back(mt.mp2 > mt.mp3); result2.push_back(mt.mp5 > mt.mp7); result2.push_back(mt.mp7 > mt.mp7);
	result2.push_back(mt.mp2 > mt.mp4); result2.push_back(mt.mp5 > mt.mp8); result2.push_back(mt.mp7 > mt.mp8);
	result2.push_back(mt.mp7 > mt.mp9); result2.push_back(mt.mp8 > mt.mp8); result2.push_back(mt.mp8 > mt.mp9);
	result2.push_back(mt.mp9 > mt.mp9);

	std::cout << std::endl;

	std::vector<int>::iterator	iter = result.begin();
	std::vector<int>::iterator	iter2 = result2.begin();
	int i = 0;

	while (iter != result.end())
	{
		if (*iter != *iter2)
			std::cout << "indice: " << i << " " << *iter << std::endl;
		i++;
		iter++;
		iter2++;
	}

	return result == result2;
}

template <class T, class V>
std::vector<int> insert_test_3(std::map<T, V> mp) {
    std::vector<int> v;
    typename std::map<T, V>::iterator it = mp.end();
    g_start1 = timer();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(it, std::make_pair(i, j));
    }
    g_end1 = timer();
    typename std::map<T, V>::iterator it2 = mp.begin();
    for (; it2 != mp.end(); ++it2) {
        v.push_back(it2->first);
        v.push_back(it2->second);
    }
    return v;
}

template <class T, class V>
std::vector<int> insert_test_3(_map<T, V> mp) {
    std::vector<int> v;
    typename _map<T, V>::iterator it = mp.end();
    g_start2 = timer();
    for (int i = 0, j = 0; i < 50 * _ratio; ++i, ++j) {
        mp.insert(it, _make_pair(i, j));
    }
    g_end2 = timer();
    typename _map<T, V>::iterator it2 = mp.begin();
    for (; it2 != mp.end(); ++it2) {
        v.push_back(it2->first);
        v.push_back(it2->second);
    }
    return v;
}

int main() {

    exit(run_map_unit_test<int, int>("insert(hint)", insert_test_3, insert_test_3));
}