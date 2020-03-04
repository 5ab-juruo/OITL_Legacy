#ifndef OITL_GRAPH_HPP
#define OITL_GARPH_HPP 1

#include "basic_calc.hpp"
#include "disjoint_set.hpp"

#if __cplusplus < 201103L
#include <list>
#else
#include <forward_list>
#endif

#include <stack>
#include <vector>

namespace oitl
{
	typedef enum { directed = 1, undirected = 2 } is_directed;
	
	#if __cplusplus >= 201103L
	
	template<typename T>
		using node_chain = std::forward_list<T>;
	
	#else
	#define node_chain std::list
	#endif
	
	template<is_directed dir, typename val_t = long long>
	class dynamic_graph;
	
	template<int n, is_directed dir, typename val_t = long long>
	class graph;
	
	template<int n, int m, is_directed dir, typename val_t = long long>
	class static_graph;
	
	namespace __oitl_builtin
	{
		template<typename T>
		class __node_t
		{
			private:
				
				__id_type __des;
				T __val;
			
			public:
				
				__node_t(__id_type __d = __id_type(), T __v = T()) : __des(__d), __val(__v) { }
				
				__id_type dest() const { return __des; }
				T value() const { return __val; }
		};
		
		template<typename __graph_type>
		bool __dfs(const __graph_type *__g, int __s, int __t, std::vector<bool>& __vis)
		{
			typedef typename __graph_type::iterator __it;
			
			if (__s == __t)
				return true;
			
			for (__it __p = __g->begin(__s); __p != __g->end(__s); ++__p)
				if (!__vis[__p->dest()])
				{
					__vis[__p->dest()] = true;
					
					if (__dfs(__g, __p->dest(), __t, __vis))
						return true;
					
					__vis[__p->dest()] = false;
				}
			
			return false;
		}
		
		template<typename __graph_type>
		void __dfs2(const __graph_type* __g, __id_type __s, std::vector<bool>& __vis)
		{
			typedef typename __graph_type::iterator __it;
			
			for (__it __p = __g->begin(__s); __p != __g->end(__s); ++__p)
				if (!__vis[__p->dest()])
				{
					__vis[__p->dest()] = true;
					__dfs2(__g, __p->dest(), __vis);
				}
		}
		
		template<typename __graph_type>
		void __tarjan(__graph_type *__g, int __s, int& __ind, int& __ret, std::vector<int>& __dfn
			, std::vector<int>& __low, std::vector<bool>& __in_stack, std::stack<int>& __sta)
		{
			typedef typename __graph_type::iterator iterator;
			
			__dfn[__s] = __low[__s] = __ind;
			++__ind;
			__in_stack[__s] = true;
			__sta.push(__s);
			
			for (iterator __p = __g->begin(__s); __p != __g.end(__s); ++__p)
			{
				if (__dfn[__p->dest()] == -1)
					__tarjan(__g, __p->dest(), __ind, __ret, __dfn, __low, __in_stack, __sta);
				else if (!__in_stack[__p->dest()])
					continue;
				
				if (__low[__p->dest()] < __low[__s])
					__low[__s] = __low[__p->dest()];
			}
			
			if (__dfn[__s] == __low[__s])
			{
				++__ret;
				
				do {
					__s = __sta.top();
					__sta.pop();
					__in_stack[__s] = false;
				} while (__dfn[__s] != __low[__s]);
			}
		}
	}
	
	template<typename val_t> class dynamic_graph<directed, val_t>
	{
		public:
			
			typedef typename node_chain<__oitl_builtin::__node_t<val_t> >::iterator iterator;
		
		private:
			
			std::vector<node_chain<__oitl_builtin::__node_t<val_t> > > __g;
		
		public:
			
			dynamic_graph() { }
			dynamic_graph(int __nd_cnt) { __g.resize(__nd_cnt); }
			dynamic_graph(const dynamic_graph<directed, val_t>& __dg)
			{
				__g.assign(__dg.__g.begin(), __dg.__g.end());
			}
			
			~dynamic_graph() { }
			
			void clear() { __g.clear(); }
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(__g.size(), __s);
				__oitl_array_assert(__g.size(), __t);
				
				__g[__s].push_back(__oitl_builtin::__node_t<val_t>(__t, __v));
			}
			
			void add_vertex() { __g.push_back(node_chain<__oitl_builtin::__node_t<val_t> >()); }
			void set_vertex(int __nd_cnt) { __g.resize(__nd_cnt); }
			__id_type vertex_cnt() const { return __g.size(); }
			
			iterator begin(int __node_id) const
			{
				__oitl_array_assert(__g.size(), __node_id);
				return __g[__node_id].begin();
			}
			
			iterator end(int __node_id) const
			{
				__oitl_array_assert(__g.size(), __node_id);
				return __g[__node_id].end();
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(__g.size(), false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			bool is_strongly_connect(int __s, int __t) const
			{
				return is_connect(__s, __t) && is_connect(__t, __s);
			}
			
			int scc_count() const
			{
				int __ans = 0, __ind;
				std::vector<int> __dfn(__g.size(), -1), __low(__g.size(), -1);
				std::vector<bool> __in_stack(__g.size(), false);
				std::stack<int> __sta;
				
				for (std::vector<int>::iterator __it = __dfn.begin()
					; __it != __dfn.end(); __it++)
					if (*__it == -1)
					{
						__ind = 0;
						
						__oitl_builtin::__tarjan(this, __it - __dfn.begin(), __ind, __ans
							, __dfn, __low, __in_stack, __sta);
					}
				
				return __ans;
			}
			
			bool is_connect() const { return scc_count() == 1; }
			
	};
	
	template<int n, typename val_t> class graph<n, directed, val_t>
	{
		public:
			
			typedef typename node_chain<__oitl_builtin::__node_t<val_t> >::iterator iterator;
		
		private:
			
			node_chain<__oitl_builtin::__node_t<val_t> > __g[n];
		
		public:
			
			graph() { }
			graph(const graph<n, directed, val_t>& __og)
			{
				for (int __i = 0; __i < n; ++__i)
					__g[__i] = __og.__g[__i];
			}
			
			~graph() { }
			
			void clear()
			{
				for (int __i = 0; __i < n; ++__i)
					__g[__i].clear();
			}
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(n, __s);
				__oitl_array_assert(n, __t);
				
				__g[__s].push_back(__oitl_builtin::__node_t<val_t>(__t, __v));
			}
			
			iterator begin(int __node_id) const
			{
				__oitl_array_assert(n, __node_id);
				return __g[__node_id].begin();
			}
			
			iterator end(int __node_id) const
			{
				__oitl_array_assert(n, __node_id);
				return __g[__node_id].end();
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(n, false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			bool is_strongly_connect(int __s, int __t) const
			{
				return is_connect(__s, __t) && is_connect(__t, __s);
			}
			
			int scc_count() const
			{
				int __ans = 0, __ind;
				std::vector<int> __dfn(n, -1), __low(n, -1);
				std::vector<bool> __in_stack(n, false);
				std::stack<int> __sta;
				
				for (std::vector<int>::iterator __it = __dfn.begin()
					; __it != __dfn.end(); __it++)
					if (*__it == -1)
					{
						__ind = 0;
						
						__oitl_builtin::__tarjan(this, __it - __dfn.begin(), __ind, __ans
							, __dfn, __low, __in_stack, __sta);
					}
				
				return __ans;
			}
			
			bool is_connect() const { return scc_count() == 1; }
			
	};
	
	template<int n, int m, typename val_t> class static_graph<n, m, directed, val_t>
	{
		private:
			
			int __hd[n], __nxt[m], __edg_cnt;
			__oitl_builtin::__node_t<val_t> __val[m];
		
		public:
			
			class iterator
			{
				private:
					
					int __pos;
				
				public:
					
					iterator(int __p = 0) : __pos(__p) { }
					iterator(const iterator &__it) : __pos(__it.__pos) { }
					
					iterator operator++() { ++__pos; return *this; }
					iterator operator--() { --__pos; return *this; }
					
					iterator operator++(int)
					{
						iterator __self = *this;
						++__pos;
						return __self;
					}
					
					iterator operator--(int)
					{
						iterator __self = *this;
						--__pos;
						return __self;
					}
					
					__oitl_builtin::__node_t<val_t>* operator->() const { return &__val[__pos]; }
			};
			
			static_graph() : __edg_cnt(0)
			{
				for (__i = 0; __i < n; ++__i)
					__hd[__i] = -__i - 1;
			}
			static_graph(const static_graph<n, m, directed, val_t>& __sg)
			{
				__edg_cnt = __sg.__edg_cnt;
				
				for (int __i = 0; __i < n; ++__i)
					__hd[__i] = __sg.__hd[__i];
				
				for (int __i = 0; __i < __edg_cnt; ++__i)
				{
					__nxt[__i] = __sg.__nxt[__i];
					__val[__i] = __sg.__val[__i];
				}
			}
			
			~static_graph() { }
			
			void clear()
			{
				__edg_cnt = 0;
				memset(__hd, -1, sizeof(__hd));
			}
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(n, __s);
				__oitl_array_assert(n, __t);
				__oitl_assert(__edg_cnt < m, "No more edges can added.");
				
				__val[__edg_cnt].__v = __v, __val[__edg_cnt].__d = __t;
				__nxt[__edg_cnt] = __hd[__s], __hd[__s] = __edg_cnt;
				
				++__edg_cnt;
			}
			
			iterator begin(int __node_id) const
			{
				__oitl_array_assert(n, __node_id);
				return iterator(__hd[__node_id]);
			}
			
			iterator end(int __node_id)
			{
				__oitl_array_assert(n, __node_id);
				return iterator(-__node_id - 1);
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(n, false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			bool is_strongly_connect(int __s, int __t) const
			{
				return is_connect(__s, __t) && is_connect(__t, __s);
			}
			
			int scc_count() const
			{
				int __ans = 0, __ind;
				std::vector<int> __dfn(n, -1), __low(n, -1);
				std::vector<bool> __in_stack(n, false);
				std::stack<int> __sta;
				
				for (std::vector<int>::iterator __it = __dfn.begin()
					; __it != __dfn.end(); ++__it)
					if (*__it == -1)
					{
						__ind = 0;
						
						__oitl_builtin::__tarjan(this, __it - __dfn.begin(), __ind, __ans
							, __dfn, __low, __in_stack, __sta);
					}
				
				return __ans;
			}
			
			bool is_connect() const { return scc_count() == 1; }
			
	};
	
	// Undirected Graphs

	template<typename val_t> class dynamic_graph<undirected, val_t>
	{
		public:
			
			typedef typename node_chain<__oitl_builtin::__node_t<val_t> >::iterator iterator;
		
		private:
			
			std::vector<node_chain<__oitl_builtin::__node_t<val_t> > > __g;
		
		public:
			
			dynamic_graph() { }
			dynamic_graph(int __nd_cnt) { __g.resize(__nd_cnt); }
			dynamic_graph(const dynamic_graph<directed, val_t>& __dg)
			{
				__g.assign(__dg.__g.begin(), __dg.__g.end());
			}
			
			~dynamic_graph() { }
			
			void clear() { __g.clear(); }
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(__g.size(), __s);
				__oitl_array_assert(__g.size(), __t);
				
				__g[__s].push_back(__oitl_builtin::__node_t<val_t>(__t, __v));
				__g[__t].push_back(__oitl_builtin::__node_t<val_t>(__s, __v));
			}
			
			void add_vertex() { __g.push_back(node_chain<__oitl_builtin::__node_t<val_t> >()); }
			void set_vertex(int __nd_cnt) { __g.resize(__nd_cnt); }
			__id_type vertex_cnt() const { return __g.size(); }
			
			iterator begin(int __node_id)
			{
				__oitl_array_assert(__g.size(), __node_id);
				return __g[__node_id].begin();
			}
			
			iterator end(int __node_id)
			{
				__oitl_array_assert(__g.size(), __node_id);
				return __g[__node_id].end();
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(__g.size(), false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			int scc_count() const
			{
				int __ans = 0;
				std::vector<bool> __vis(__g.size(), false);
				
				for (int __i = 0; __i < __nd_cnt; ++__i)
					if (!__vis[__i])
					{
						__vis[__i] = true;
						__dfs2(this, __i, __vis);
						++__ans;
					}
				
				return __ans;
			}
			
			bool is_connect() const { return scc_count() == 1; }
	};
	
	template<int n, typename val_t> class graph<n, undirected, val_t>
	{
		public:
			
			typedef typename node_chain<__oitl_builtin::__node_t<val_t> >::iterator iterator;
		
		private:
			
			node_chain<__oitl_builtin::__node_t<val_t> > __g[n];
		
		public:
			
			graph() { }
			graph(const graph<directed, val_t>& __og)
			{
				for (int __i = 0; __i < n; ++__i)
					__g[__i] = __og.__g[__i];
			}
			
			~graph() { }
			
			void clear()
			{
				for (int __i = 0; __i < n; ++__i)
					__g[__i].clear();
			}
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(n, __s);
				__oitl_array_assert(n, __t);
				
				__g[__s].push_back(__oitl_builtin::__node_t<val_t>(__t, __v));
				__g[__t].push_back(__oitl_builtin::__node_t<val_t>(__s, __v));
			}
			
			iterator begin(int __node_id)
			{
				__oitl_array_assert(n, __node_id);
				return __g[__node_id].begin();
			}
			
			iterator end(int __node_id)
			{
				__oitl_array_assert(n, __node_id);
				return __g[__node_id].end();
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(n, false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			int scc_count() const
			{
				int __ans = 0;
				std::vector<bool> __vis(n, false);
				
				for (int __i = 0; __i < __nd_cnt; ++__i)
					if (!__vis[__i])
					{
						__vis[__i] = true;
						__oitl_builtin::__dfs2(this, __i, __vis);
						++__ans;
					}
				
				return __ans;
			}
			
			bool is_connect() const { return scc_count() == 1; }
	};
	
	template<int n, int m, typename val_t> class static_graph<n, m, undirected, val_t>
	{
		private:
			
			__id_type __hd[n], __nxt[m<<1], __edg_cnt;
			__oitl_builtin::__node_t<val_t> __val[m<<1];
		
		public:
			
			class iterator
			{
				private:
					
					int __pos;
				
				public:
					
					iterator(int __p = 0) : __pos(__p) { }
					iterator(const iterator &__it) : __pos(__it.__pos) { }
					
					iterator operator++() { ++__pos; return *this; }
					iterator operator--() { --__pos; return *this; }
					
					iterator operator++(int)
					{
						iterator __self = *this;
						++__pos;
						return __self;
					}
					
					iterator operator--(int)
					{
						iterator __self = *this;
						--__pos;
						return __self;
					}
					
					__oitl_builtin::__node_t<val_t>* operator->() const { return &__val[__pos]; }
			};

			static_graph() : __edg_cnt(0)
			{
				for (int __i = 0; __i < n; ++__i)
					__hd[__i] = -__i - 1;
			}
			static_graph(const static_graph<n, m, directed, val_t>& __sg)
			{
				__edg_cnt = __sg.__edg_cnt;
				
				for (int __i = 0; __i < n; ++__i)
					__hd[__i] = __sg.__hd[__i];
				
				for (int __i = 0; __i < __edg_cnt; ++__i)
				{
					__nxt[__i] = __sg.__nxt[__i];
					__val[__i] = __sg.__val[__i];
				}
			}
			
			~static_graph() { }
			
			void clear() { __g.clear(); }
			
			void add_edge(int __s, int __t, val_t __v)
			{
				__oitl_array_assert(n, __s);
				__oitl_array_assert(n, __t);
				
				__val[__edg_cnt].__des = __t, __val[__edg_cnt].__val = __v;
				__nxt[__edg_cnt] = __hd[__s], hd[__s] = __edg_cnt;
				++__edg_cnt;

				__val[__edg_cnt].__des = __s, __val[__edg_cnt].__val = __v;
				__nxt[__edg_cnt] = __hd[__t], __hd[__t] = __edg_cnt;
				++__edg_cnt;
			}

			iterator begin(int __node_id)
			{
				__oitl_array_assert(n, __node_id);
				return iterator(__hd[__node_id]);
			}
			
			iterator end(int __node_id)
			{
				__oitl_array_assert(n, __node_id);
				return iterator(-__node_id - 1);
			}
			
			bool is_connect(int __s, int __t) const
			{
				std::vector<bool> __vis(__g.size(), false);
				
				__vis[__s] = true;
				return __oitl_builtin::__dfs(this, __s, __t, __vis);
			}
			
			int cc_count() const
			{
				int __ans = 0;
				std::vector<bool> __vis(__g.size(), false);
				
				for (int __i = 0; __i < __nd_cnt; ++__i)
					if (!__vis[__i])
					{
						__vis[__i] = true;
						__dfs2(this, __i, __vis);
						++__ans;
					}
				
				return __ans;
			}
			
			bool is_connect() const { return cc_count() == 1; }
	};
}

#endif
