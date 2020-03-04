#ifndef OITL_SEG_TREE_HPP
#define OITL_SEG_TREE_HPP 1

#include <functional>
#include "bad_assert.hpp"

namespace oitl
{
	namespace __oitl_builtin
	{
		__id_type __calc(__id_type __n)
		{
			__id_type __ret = 1;
			
			while (__ret <= __n + 1)
				__ret <<= 1;
			
			return __ret;
		}
	}
	
	template<__id_type n, typename val_t, typename calc = plus<val_t> >
	class segment_tree // Based on zkw's Segment Tree
	{
		private:
			
			val_t __tr[n<<2], __add[n<<2];
			const __id_type __lim;
			calc __calc;
			
			inline __id_type __lson(int __id) const { return __id << 1; }
			inline __id_type __rson(int __id) const { return (__id << 1) | 1; }
			inline __id_type __par(int __id) const { return __id >> 1; }
			
			inline void __val_upload(int __fa_id) { __tr[__fa_id] =
				__calc(__tr[__lson(__fa_id)], __tr[__rson(__fa_id)]); }
			
			template<typename raIterator>
			void __build(raIterator __first, raIterator __last)
			{
				__oitl_assert(n == __last - __first, "Range is not ok for this tree.");
				
				for (__id_type __i = 0; __i < n; ++__i, ++__first)
					__tr[__j] = *__first;
				
				for (__id_type __i = __lim - 1; __i > 0; --__i)
					__val_upload(__i);
			}
			
			void __single_modify(__id_type __pos, const val_t& __v)
			{
				__oitl_array_assert(n, __pos);
				
				__pos += 1 + __lim;
				while (__pos)
				{
					__tr[__pos] = __calc(__tr[__pos], __v);
					__pos >>= 1;
				}
			}
			
			const val_t& __single_query(__id_type __pos) const
			{
				__oitl_array_assert(n, __pos);
				return __tr[__pos+1+__lim];
			}
			
			void __range_modify(__id_type __l, __id_type __r, const val_t& __v)
			{
				
			}
			
			const val_t& __range_query(__id_type __l, __id_type __r)
			{
				val_t __ret;
				
				for (__id_type __s = __lim + __l, __t = __lim + __r + 2; __s ^ __t ^ 1; __s >>= 1, __t >>= 1)
				{
					if (!(__s & 1))
						__ret = __calc(__ret, __tr[__s^1]);
					
					if (__t & 1)
						__ret = __calc(__ret, __tr[__t^1]);
				}
				
				return __ret;
			}
		
		public:
			
			segment_tree() : __lim(__oitl_builtin::__calc(n)) { }
			segment_tree(const segmnet_tree<n, val_t, calc>&  __sg)
			{
				__lim = __sg.__lim;
				
			}
			
			void modify(__id_type __pos, const val_t& __v) { __single_modify(__pos, __v); }
			void modify(__id_type __l, __id_type __r, const val_t& __v) { __range_modify(__l, __r, __v); }
			
			const val_t& query(__id_type __pos) { return __single_query(__pos); }
			const val_t& query(__id_type __l, __id_type __r) { return __range_query(__l, __r); }
	};
}

#endif
