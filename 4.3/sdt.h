//------------------------------------------------------------------------------
//
// sdt.h
//
// Учебный заголовочный файл для курса "Технология программирования" кафедры
// Управления и информатики НИУ "МЭИ". Основан на std_lib_facilities.h книги
// "Programming Principles and Practices Using C++, 2nd Edition" Б. Страуструпа.
// Комментарии к оригинальному файлу перемещены в конец.
//
// Студентам:
//     1) В начале курса разбирать и понимать этот файл не нужно, 
//        к концу курса вы научитесь обходиться без него.
//     2) Стандартные заголовочные файлы, которые подключает этот,
//        хорошо описаны на сайте C++ Reference (http://cppreference.com).
//
//------------------------------------------------------------------------------

#ifndef SOFTWARE_DEVELOPMENT_TECHNOLOGY_H
#define SOFTWARE_DEVELOPMENT_TECHNOLOGY_H 0

#include <iostream>		 // Стандартный ввод и вывод (cin, cout, getline).
#include <iomanip>		 // Форматирование ввода и вывода (setw, setprecision).
#include <fstream>		 // Файловый ввод и вывод (ifstream, ofstream).
#include <sstream>		 // Ввод и вывод в строку в памяти (i/ostringstream).
#include <cmath>		 // Математические функции.
#include <cstdlib>		 // Вспомогательные функции (exit).
#include <string>		 // Строки (string).
#include <list>			 // Двусвязный список (list).
#include <forward_list>  // Односвязный список (forward_list).
#include <vector>		 // Вектор (vector :-).
#include <map> 			 // Ассоциативный упорядоченный массив (map).
#include <unordered_map> // Хэш-таблица (unordered_map).
#include <algorithm>	 // Алгоритмы (find, sort).
#include <array>		 // Массив в стиле C++ (array).
#include <regex>		 // Регулярные выражения (regex_***).
#include <random>		 // Генераторы псевдослучайных чисел.
#include <stdexcept>	 // Стандартные исключения (exception, ***_error).

typedef long Unicode;

// Никогда не следует так делать в реальных заголовочных файлах!
using namespace std;

template<class T> string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

struct Range_error : out_of_range {	// enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};


// trivially range-checked vector (no iterator checking):
template< class T> struct Vector : public std::vector<T> {
	using size_type = typename std::vector<T>::size_type;

#ifdef _MSC_VER
	// microsoft doesn't yet support C++11 inheriting constructors
	Vector() { }
	explicit Vector(size_type n) :std::vector<T>(n) {}
	Vector(size_type n, const T& v) :std::vector<T>(n,v) {}
	template <class I>
	Vector(I first, I last) : std::vector<T>(first, last) {}
	Vector(initializer_list<T> list) : std::vector<T>(list) {}
#else
	using std::vector<T>::vector;	// inheriting constructor
#endif

	T& operator[](unsigned int i) // rather than return at(i);
	{
		if (i<0||this->size()<=i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
	const T& operator[](unsigned int i) const
	{
		if (i<0||this->size()<=i) throw Range_error(i);
		return std::vector<T>::operator[](i);
	}
};

// disgusting macro hack to get a range checked vector:
#define vector Vector

// trivially range-checked string (no iterator checking):
struct String : std::string {
	using size_type = std::string::size_type;
//	using string::string;

	char& operator[](unsigned int i) // rather than return at(i);
	{
		if (size()<=i) throw Range_error(i);
		return std::string::operator[](i);
	}

	const char& operator[](unsigned int i) const
	{
		if (size()<=i) throw Range_error(i);
		return std::string::operator[](i);
	}
};


namespace std 
{

template<> struct hash<String>
{
    size_t operator()(const String& s) const
    {
        return hash<std::string>()(s);
    }
};

} // namespace std


struct Exit : runtime_error {
	Exit(): runtime_error("Exit") {}
};

// Возбуждает исключение runtime_error() с текстом "файл:строка: message".
//
// Это не функция, а так называемый макрос. При использовании, например, так:
//		error("something happened!");
// компилятор подставит на место "вызова" макроса код ниже под #define, причем
// вместо message в коде будет "something happened!", а специальные макросы
// __FILE__ и __LINE__ будут заменены на строку с полным именем файла программы 
// и строку в нем, откуда был "вызван" макрос error(). Из __FILE__ извлекается 
// затем имя файла без пути). 
//
// Обратные косые черты в конце строки приказывают компилятору толковать 
// следующую строку как продолжение предыдущей (как ключевое слово ... 
// в MATLAB). Цикл do { } while (0) нужен затем, чтобы после "вызова" error() 
// можно было поставить точку с запятой; кроме того, в теле цикла объявляются 
// временные переменные.
//
#define error(message) 														   \
	do 																		   \
	{ 																		   \
		string const path = __FILE__; 										   \
		auto   const last_slash = path.find_last_of('/'); 					   \
		string const name = 												   \
			last_slash != string::npos ? path.substr(last_slash + 1) : path;   \
		string const what = 												   \
			name + ":" + to_string(__LINE__) + ": " + to_string((message));    \
		throw runtime_error(what);	 										   \
	} while (0)


template<class T> char* as_bytes(T& i)	// needed for binary I/O
{
	void* addr = &i;	// get the address of the first byte
						// of memory used to store the object
	return static_cast<char*>(addr); // treat that memory as bytes
}


inline void keep_window_open()
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Press ENTER to exit...\n";
	cin.get();
}

inline void keep_window_open(const string& terminator)
{
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	do
	{
		cout << "Please enter " << terminator << " to exit: ";
		string input;
		cin >> input;
		if (input == terminator)
		{
			return;
		}
	}
	while (true);
}



// error function to be used (only) until error() is introduced in Chapter 5:
inline void simple_error(string s)	// write ``error: s and exit program
{
	cerr << "error: " << s << '\n';
	keep_window_open();		// for some Windows environments
	exit(1);
}

// make std::min() and std::max() accessible on systems with antisocial macros:
#undef min
#undef max


// run-time checked narrowing cast (type conversion). See ???.
template<class R, class A> R narrow_cast(const A& a)
{
	R r = R(a);
	if (A(r)!=a) error(string("info loss"));
	return r;
}

// random number generators. See 24.7.



inline int randint(int min, int max) { static default_random_engine ran; return uniform_int_distribution<>{min, max}(ran); }

inline int randint(int max) { return randint(0, max); }

//inline double sqrt(int x) { return sqrt(double(x)); }	// to match C++0x

// container algorithms. See 21.9.

template<typename C>
using Value_type = typename C::value_type;

template<typename C>
using Iterator = typename C::iterator;

template<typename C>
	// requires Container<C>()
void sort(C& c)
{
	std::sort(c.begin(), c.end());
}

template<typename C, typename Pred>
// requires Container<C>() && Binary_Predicate<Value_type<C>>()
void sort(C& c, Pred p)
{
	std::sort(c.begin(), c.end(), p);
}

template<typename C, typename Val>
	// requires Container<C>() && Equality_comparable<C,Val>()
Iterator<C> find(C& c, Val v)
{
	return std::find(c.begin(), c.end(), v);
}

template<typename C, typename Pred>
// requires Container<C>() && Predicate<Pred,Value_type<C>>()
Iterator<C> find_if(C& c, Pred p)
{
	return std::find_if(c.begin(), c.end(), p);
}

#endif // SOFTWARE_DEVELOPMENT_TECHNOLOGY_H


//------------------------------------------------------------------------------
// Комментарии к оригинальному файлу std_lib_facilities.h:

/*
   std_lib_facilities.h
*/

/*
	simple "Programming: Principles and Practice using C++ (second edition)" course header to
	be used for the first few weeks.
	It provides the most common standard headers (in the global namespace)
	and minimal exception/error support.

	Students: please don't try to understand the details of headers just yet.
	All will be explained. This header is primarily used so that you don't have
	to understand every concept all at once.

	By Chapter 10, you don't need this file and after Chapter 21, you'll understand it

	Revised April 25, 2010: simple_error() added

	Revised November 25 2013: remove support for pre-C++11 compilers, use C++11: <chrono>
	Revised November 28 2013: add a few container algorithms
	Revised June 8 2014: added #ifndef to workaround Microsoft C++11 weakness
*/