#ifndef _OITL_ASSETS_BINARY_INDEXED_TREE
#define _OITL_ASSETS_BINARY_INDEXED_TREE

 #if __cplusplus >= 201103L
 #include <array>
 #endif

namespace oitl
{
	namespace __oitl_builtin
	{
		inline int __lowbit(int __x) { return __x & -__x; }
	}

	template<int _N, class _Val_t, class _Op>
	class binary_indexed_tree
	{
		public:
			typedef _Val_t value_type;
			typedef _Op operate_type;
		
		private:
			
			#if __cplusplus >= 201103L
			std::array<value_type, _N + 1> __bit;
			#else
			value_type __bit[_N + 1];
			#endif 

			operate_type __calc;
			value_type __identity;

			void _Add(const int __ptr, value_type __val)
			{
				register int __i = __ptr;

				while (__i <= _N)
				{
					__bit[__i] = __calc(__bit[__i], __val);
					__i += __oitl_builtin::__lowbit(__i);
				}
			}

			value_type _Get(const int __ptr) const
			{
				register int __i = __ptr;
				value_type __ret = __identity;

				while (__i > 0)
				{
					__ret = __calc(__ret, __bit[__i]);
					__i -= __oitl_builtin::__lowbit(__i);
				}

				return __ret;
			}
		
		public:

			binary_indexed_tree(value_type _Identity = value_type(0)) : __identity(_Identity)
			{
				#if __cplusplus >= 201103L
				__bit.fill(__identity);
				#else
				for (register int __i = 0; __i < _N; ++__i)
					__bit[__i] = __identity;
				#endif
			}

			void modify(int __ptr, _Val_t __val)
			{
				_Add(__ptr + 1, __val);
			}

			value_type query(int __qr)
			{
				return _Get(__qr + 1);
			}
	};
}

#endif