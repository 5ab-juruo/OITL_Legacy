#ifndef OITL_SPARSE_TABLE_HPP
#define OITL_SPARSE_TABLE_HPP

#include <vector>

namespace oitl
{
    template<int n, typename val_t = long long>
    class sparse_table
    {
        private:

            struct __line
            {
                __id_type __up;
                val_t __rmq[n];
            };

            std::vector<__line> __tab;

            template<typename it>
            void build(it __l, it __r)
            {

            }
        
        public:

            sparse_table() { }
            sparse_table(const sparse_table<n, val_t>& __st)
            {

            }

            ~sparse_table() { }
    };
}

#endif