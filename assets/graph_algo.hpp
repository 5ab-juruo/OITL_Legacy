#ifndef OITL_GRAPH_ALGO_HPP
#define OITL_GRAPH_ALGO_HPP 1

namespace oitl
{
    namespace __oitl_builtin
	{
		void __strict_random_graph(int n, int m)
		{
		}
		
		template<is_diredted dir, typename val_t>
		__id_type __get_node(const dynamic_graph<dir, val_t>& __dg) { return __dg.vertex_cnt(); }
		
		template<int n, is_diredted dir, typename val_t>
		__id_type __get_node(const graph<n, dir, val_t>& __og) { return n; }
		
		template<int n, int m, is_diredted dir, typename val_t>
		__id_type __get_node(const static_graph<n, m, dir, val_t>& __dg) { return n; }
	}
	
	template<typename __graph_type>
	void fill_graph(__graph_type& __res)
	{
		typename __graph_type::iterator __it;
		__id_type __nd = __get_node(__res);
		
		for (__it)
	}
}

#endif