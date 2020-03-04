#ifndef OITL_BAD_ASSERT_HPP
#define OITL_BAD_ASSERT_HPP

#include <exception>
#include <cassert>
#include <string>

namespace oitl
{
	class std_error : public std::exception
	{
		private:
			
			std::string s;
		
		public:
			
			std_error(const std::string &_s = "") : s("[OI Template Library] " + _s) { }
			~std_error() { s.clear(); }
			
			const char* what() { return s.c_str(); }
	};
	
	void __oitl_assert(bool assertion, const std::string &s)
	{
		if (!assertion)
			throw std_error(s);
	}
	
	// Some spacial assertions
	
	template<typename T>
	void __oitl_range_assert(const T &a, const T &b)
	{
		__oitl_assert(a <= b, "Input not make a range.");
	}
	
	// Check the range [l, r]
	template<typename T>
	void __oitl_in_range_assert(const T& l, const T& r, const T& ps)
	{
		__oitl_assert(l <= ps && ps <= r, "Position is not in the range.");
	}
	
	void __oitl_array_assert(const int& len, const int& id)
	{
		__oitl_assert(id >= 0 && len > id, "Visit out of array.");
	}
}

#endif 
