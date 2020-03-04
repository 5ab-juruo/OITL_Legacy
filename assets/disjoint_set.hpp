#ifndef OITL_DISJOINT_SET_HPP
#define OITL_DISJOINT_SET_HPP 1

#include "bad_assert.hpp"
#include <vector>

namespace oitl
{
	class disjoint_set
	{
		private:
			
			std::vector<__id_type> __v;
			
			__id_type __find(__id_type __id)
			{
				if (__v[__id] != __id)
					__v[__id] = __find(__v[__id]);
				
				return __v[__id];
			}
		
		public:
			
			disjoint_set(__id_type __size = 0)
			{
				__v.resize(__size);
				
				for (int __i = 0; __i < __size; ++__i)
					__v[__i] = __i;
			}
			disjoint_set(const disjoint_set& __ds) { __v.assign(__ds.__v.begin(), __ds.__v.end()); }
			~disjoint_set() { }
			
			void resize(__id_type __nsize)
			{
				__oitl_assert(__nsize > __v.size(), "Not enough spaces.");
				__v.resize(__id_type);
			}
			
			void clear() { __v.clear(); }
			bool is_lone(__id_type __i) const
			{
				__oitl_array_assert(__v.size(), __i);
				return __v[__i] == __i;
			}
			bool is_same(__id_type __id1, __id_type __id2)
			{
				__oitl_array_assert(__v.size(), __id1);
				__oitl_array_assert(__v.size(), __id2);
				
				return __find(__id1) == __find(__id2);
			}
			
			void unite(__id_type __id1, __id_type __id2)
			{
				__oitl_array_assert(__v.size(), __id1);
				__oitl_array_assert(__v.size(), __id2);
				
				if (is_same(__id1, __id2))
					return;
				
				__v[__find(__id1)] = __find(__id2);
			}
	};
}

#endif
