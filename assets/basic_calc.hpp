#ifndef OITL_BASIC_CALC_HPP
#define OITL_BASIC_CALC_HPP 1

namespace oitl
{
	inline int __oitl_min(int a, int b) { return (a < b)? a:b; }
	inline int __oitl_max(int a, int b) { return (a > b)? a:b; }
}

#endif 
