#ifndef _OITL_ASSETS_SPARSE_TABLE
#define _OITL_ASSETS_SPARSE_TABLE 1

#include <vector>

#if __cplusplus >= 201103L
#include <array>
#endif

namespace oitl
{
	namespace __oitl_builtin
	{
		template<int _N>
		class _Pow_tab
		{
			private:

				#if __cplusplus >= 201103L
				std::array<int, _N> __val;
				#else
				int __val[_N];
				#endif
			
			public:

				_Pow_tab()
				{
					int __lay = -1, __pw = 1;

					for (register int __i = 0; __i < _N; ++__i)
					{
						if (__pw == __i)
							++__lay, __pw <<= 1;
						
						__val[__i] = __lay;
					}
				}

				int operator[](int id) const
				{
					return __val[id];
				}
		};
	}

	template<int _N, class _Val_t, class _Op>
	class sparse_table
	{
		public:

			typedef _Val_t value_type;
			typedef _Op operate_type;
		
		private:

			std::vector<std::vector<value_type> > __tab;
			__oitl_builtin::_Pow_tab<_N> __ask;

			operate_type __calc;
		
		public:

			sparse_table() { }

			template<typename _Iterator>
			void refill(_Iterator __lp)
			{
				register int __cra = 1, __ptr = 0, __tar = 0;
				_Iterator __rp = __lp;

				__tab.clear();
				__tab.push_back(std::vector<value_type>(_N));
				
				for (register int __i = 0; __i < _N; ++__i)
					++__rp;
				__tab[0].assign(__lp, __rp);

				while (__tab[__ptr].size() > __cra)
				{
					++__ptr;
					__tab.push_back(std::vector<value_type>());

					for (register int __i = __cra; __i < __tab[__tar].size(); ++__i)
						__tab[__ptr].push_back(__calc(__tab[__tar][__i-__cra], __tab[__tar][__i]));

					++__tar, __cra <<= 1;
				}
			}

			value_type query(int __lp, int __rp) const
			{
				return __calc(__tab[__ask[__rp-__lp]][__lp],
							  __tab[__ask[__rp-__lp]][__rp-(1<<__ask[__rp-__lp])]);
			}
	};
}

#endif