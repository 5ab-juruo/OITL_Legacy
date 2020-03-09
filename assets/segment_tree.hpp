#ifndef OITL_SEG_TREE_HPP
#define OITL_SEG_TREE_HPP 1

#include <functional>
#include <vector>
#include "bad_assert.hpp"

namespace oitl
{
	namespace __oitl_builtin
	{
		OITL_CONSTEXPR __id_type __calc_size(__id_type __n)
		{
			__id_type __ret = 1;
			
			while (__ret <= __n + 1)
				__ret <<= 1;
			
			return __ret;
		}

		OITL_CONSTEXPR __id_type __calc_size2(__id_type __n)
		{
			__id_type __ret = 1;
			
			while (__ret <= __n)
				__ret <<= 1;
			
			return __ret << 1;
		}
	}

	template<__id_type __n, typename __vtype, typename __calc = std::plus<__vtype> >
	class segment_tree
	{
		private:

			std::vector<__vtype> __tr, __tag;
			__id_type __tree_size;
			__calc __calc_op;

			inline __id_type __lson(__id_type __id) { return (__id << 1); }
			inline __id_type __rson(__id_type __id) { return (__id << 1) | 1; }

			template<typename __iterator_t>
			void __build(__iterator_t __begin, __id_type __lp, __id_type __rp, __id_type __current_id)
			{
				__tag[__current_id] = 0;

				if (__lp == __rp)
				{
					__tr[__current_id] = *(__begin + __lp - 1);
					return;
				}

				__id_type __mid = (__lp + __rp) >> 1;

				__build(__begin, __lp, __mid, __lson(__current_id));
				__build(__begin, __mid + 1, __rp, __rson(__current_id));

				__tr[__current_id] = __calc_op(__tr[__lson(__current_id)], __tr[__rson(__current_id)]);
			}

			void __modify(__id_type __id, __id_type __id_l, __id_type __id_r, __id_type __current_id, __vtype __val)
			{
				if (__id_l == __id_r)
				{
					__tr[__current_id] = __val;
					return;
				}

				__id_type __mid = (__id_l + __id_r) >> 1;

				if (__id_l <= __id && __id <= __mid)
					modify(__id, __id_l, __mid, __lson(__current_id), __val);
				else
					modify(__id, __mid + 1, __r, __rson(__current_id), __val);
				
				__tr[__current_id] = __calc_op(__tr[__lson(__current_id)], __tr[__rson(__current_id)]);
			}

			void __modify(__id_type __lp, __id_type __rp, __id_type __id_l, __id_type __id_r, __id_type __current_id, __vtype __val)
			{
				if (__lp <= __id_l && __id_r <= __rp)
				{
					__tag[__current_id] = __calc_op(__tag[__current_id], __val);
					return;
				}

				__id_type __mid = (__id_l + __id_r) >> 1;

				if (__lp <= __mid && __id_l <= __rp)
					__modify(__lp, __rp, __id_l, __mid, __lson(__current_id), __val);
				if (__lp <= __id_r && __mid < __rp)
					__modify(__lp, __rp, __mid + 1, __id_r, __rson(__current_id), __val));
			}

			__vtype __query(__id_type __pos, __id_type __id_l, __id_type __id_r, __id_type __current_id)
			{
				if (__id_l == __id_r)
				{
					return __calc_op(__tr[__current_id], __tag[__current_id]);
				}

				__id_type __mid = (__id_l + __id_r) >> 1;

				if (__id_l <= pos && pos <= __id_r)
					return __calc_op(__tag[__current_id], __query(__pos, __id_l, __mid, __lson(__current_id)));
				else
					return __calc_op(__tag[__current_id], __query(__pos, __mid + 1, __id_r, __rson(__current_id)));
			}
			
			__vtype __query(__id_type __lp, __id_type __rp, __id_type __id_l, __id_type __id_r, __id_type __current_id)
			{
				
			}

		public:

			segment_tree() : __tree_size(__calc_size2(__n))
			{
				__tr.resize(__tree_size);
				__tag.resize(__tree_size);
			}

			template<typename __iterator_t>
			segment_tree(__iterator_t __begin)
			{
				__build(__begin, 1, __n, 1);
			}

			segment_tree(const segment_tree<__n, __vtype, __calc>& __seg)
			{
				__tr.assign(__seg.__tr.begin(), __seg.__tr.end());
				__tag.assign(__seg.__tag.begin(), __seg.__tag.end());
			}

			~segment_tree() { }

			void modify(__id_type __id, __vtype __val)
			{
				__modify(__id, 1, __n, 1, __val);
			}

			void modify(__id_type __lp, __id_type __rp, __vtype __val)
			{
				__modify(__lp, __rp, 1, __n, 1, __val);
			}

			__vtype query(__id_type __pos)
			{
				return __query(__pos, 1, __n, 1);
			}
			
			__vtype query(__id_type __id_l, __id_type __id_r)
			{
				__vtype(__id_l, __id_r, 1, __n, 1);
			}
	}
	
	/*
	template<__id_type n, typename val_t, typename calc = plus<val_t> >
	class segment_tree // Based on zkw's Segment Tree
	{
		private:
			
			val_t __tr[n<<2];
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
	*/
}

#endif
