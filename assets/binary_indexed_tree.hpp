#ifndef OITL_BINARY_INDEXED_TREE_HPP
#define OITL_BINARY_INDEXED_TREE_HPP 1

#include <functional>
#include <cstring>

namespace oitl
{
    template<int n, typename val_t = long long, typename calc = plus<val_t> >
    class binary_indexed_tree
    {
        private:

            val_t __tr[n+1];
            calc __calc;

            __id_type __low_bit(__id_type __id) const { return __id & -__id; }
        
        public:

            binary_indexed_tree()
            {
                memset(__tr, 0, sizeof(__tr));
            }
            binary_indexed_tree(const binary_indexed_tree<n, val_t, calc> __bit)
            {
                for (int __i = 1; __i <= n; ++__i)
                    __tr[__i] = __bit.__tr[__i];
            }

            ~binary_indexed_tree() { }

            void modify(__id_type __pos, val_t __val)
            {
                __oitl_array_assert(n, __pos);

                for (int __i = __pos + 1; __i <= n; __i += __low_bit(__i))
                    __tr[__i] = __calc(__tr[__i], __val);
            }

            val_t query(__id_type __last)
            {
                __oitl_array_assert(n, __last);

                val_t __res = val_t();

                for (int __i = __last + 1; __i > 0; __i -= __low_bit(__i))
                    __res = __calc(__res, __tr[__i]);
                
                return __res;
            }
    };

    template<int n, typename val_t>
    class range_binary_indexed_tree
    {
        private:

            binary_indexed_tree<n, val_t, plus<val_t> > __bit1, __bit2;
            calc2 __calc;
        
        public:

            range_binary_indexed_tree() { }
            range_binary_indexed_tree(const range_binary_indexed_tree& __rbit) : __bit1(__rbit.__bit1), __bit2(__rbit.__bit2) { }

            ~range_binary_indexed_tree() { }

            void modify(__id_type __pos, val_t __val) { __bit2.modify(__pos, __val); }
            void modify(__id_type __l, __id_type __r, val_t __val)
            {
                __oitl_range_assert(__l, __r);

                __bit1.modify(__l, __val);
                __bit1.modify(__r + 1, -__val);

                __bit2.modify(__l, -__val * (__l - 1))
                __bit2.modify(__r + 1, __val * __r);
            }

            val_t query(__id_type __last) const
            {
                return __bit1.query(__last) * (__last + 1) + __bit2.query(__last);
            }
    };
}

#endif