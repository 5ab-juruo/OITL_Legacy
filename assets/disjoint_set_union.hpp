#ifndef _OITL_ASSETS_DISJOINT_SET_UNION
#define _OITL_ASSETS_DISJOINT_SET_UNION 1

#include <vector>

namespace oitl
{
	class disjoint_set_union
	{
		private:

			std::vector<int> __dsu;

			int _Find_root(int __id)
			{
				if (__id != __dsu[__id])
					__dsu[__id] = _Find_root(__dsu[__id]);
				
				return __dsu[__id];
			}
		
		public:

			explicit disjoint_set_union(int __siz = 0)
			{
				__dsu.resize(__siz);
				for (register int __i = 0; __i < __siz; ++__i)
					__dsu[__i] = __i;
			}
		
			bool empty() const { return __dsu.size() == 0; }
			int size() const { return __dsu.size(); }
			void clear() { __dsu.clear(); }

			bool same_set(int __ap, int __bp)
			{
				return _Find_root(__ap) == _Find_root(__bp);
			}

			void unite(int __ap, int __bp)
			{
				if (same_set(__ap, __bp))
					return;
				
				__dsu[_Find_root(__ap)] = _Find_root(__bp);
			}

			int add_element()
			{
				__dsu.push_back(__dsu.size());
				return __dsu.size() - 1;
			}

			void reset()
			{
				for (register int __i = 0; __i < __dsu.size(); ++__i)
					__dsu[__i] = __i;
			}

			void resize(int __siz)
			{
				if (__siz > __dsu.size())
				{
					for (register int __i = __dsu.size(); __i < __siz; ++__i)
						__dsu.push_back(__i);
				}
				else
				{
					for (register int __i = 0; __i < __siz; ++__i)
						if (_Find_root(__i) >= __siz)
						{
							__dsu[_Find_root(__i)] = __i;
							__dsu[__i] = __i;
						}
					
					__dsu.resize(__siz);
				}
			}
	};
}

#endif