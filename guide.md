# Olympiad in Informatics Template Library Using Guide | OI 标准库 使用指南

## Simpified Chinese | 简体中文版
`OITL` 是一个由众多算法和数据结构所构成的一些库的统称。

想要玩转 `OITL`？看这里！

下面将会讲述不同库、类和函数的用法。

注：所有的类和函数都是在 `oitl` 名字空间下的。
### oitl/segment_tree
这个库里面有各种各样的线段树。
#### class segment_tree | oitl/assets/segment_tree.hpp
最基本的线段树，基于递归式线段树实现。

定义：`template<int __s, typename __vtype = long long, typename __calc = plus<__vtype> > class segment_tree`

- `int __s`：指区间长度；
- `typename __vtype`：指存储类型；
- `typename __calc`：指要进行区间的运算

方法：

> `segment_tree<__s, __vtype, __calc>::segment_tree()`（构造函数）

构造一个长度为 `__s`，初始值为 `__vtype()` 的区间。

> `segment_tree<__s, __vtype, __calc>::segment_tree(__vtype *arr)`（构造函数）

将 `arr` 中的值复制到线段树内，并且通过 `__calc::operator()` 构建树。

> `void segment_tree<__s, __vtype, __calc>::modify(__id_type __id, __vtype __v)`（单点修改）

将第 `__id` 个元素的值 `__ov` 赋为 `__v`。

> `void segment_tree<__s, __vtype, __calc>::modify(__id_type __lp, __id_type __rp, __vtype __v)`（区间修改）

将第 `__lp` 个元素到第 `__rp` 个元素都赋为 **`__calc::operator(__ov, __v)`**。

> `const __vtype segment_tree<__s, __vtype, __calc>::query(__id_type __id)`（单点查询）

询问第 `__id` 个数的值。

> `const __vtype segment_tree<__s, __vtype, __calc>::query(__id_type __lp, __id_type __rp)`（区间查询）

询问从第 `__lp` 个到 `__rp` 的 `__calc` 值。

#### class nontag_segment_tree | oitl/assets/segment_tree.hpp
与 `segment_tree` 类似，但是不打懒标记，也就是不支持区间修改。

定义等与 `segment_tree` 类似，不再赘述了。
#### class presistent_basic_segment_tree | oitl/assets/presistent_segment_tree.hpp
基本的线段树可持久化，就是 `nontag_segment_tree` 的可持久化版本。

定义：同 `nontag_segment_tree`。

方法：

> `presistent_basic_segment_tree<__s, __vtype, __calc>::presistent_basic_segment_tree()`（构造函数）

构造一个长度为 `__s`，初始值为 `__vtype()` 的区间。

> `presistent_basic_segment_tree<__s, __vtype, __calc>::presistent_basic_segment_tree(__vtype *arr)`（构造函数）

将 `arr` 中的值复制到线段树内，并且通过 `__calc::operator()` 构建树。

> `const __id_type presistent_basic_segment_tree<__s, __vtype, __calc>::modify(__id_type __id, __vtype __v, __id_type __ver_from)`（单点修改）

将第 `__ver_from` 个版本的第 `__id` 个元素的值 `__ov` 修改成 `__v`，返回成功后的版本号。若不成功，返回 `-1`。

> `const __vtype presistent_basic_segment_tree<__s, __vtype, __calc>::query(__id_type __id, __id_type __ver_from)`（单点查询）

查询第 `__ver_from` 个版本的第 `__id` 个值。

> `const __vtype presistent_basic_segment_tree<__s, __vtype, __calc>::query(__id_type __lp, __id_type __rp, __id_type __ver_from)`（区间查询）

查询第 `__ver_from` 个版本从 `__lp` 到 `__rp` 的值。

> `const __id_type presistent_basic_segment_tree<__s, __vtype, __calc>::copy_ver_from(__id_type __ver_from)`

从第 `__ver_from` 拷贝一个新版本，成功则返回版本号，失败返回 `-1`。

> `const void presistent_basic_segment_tree<__s, __vtype, __calc>::inver_modify(__id_type __id, __vtype __v, __id_type __ver_from)`
> 
> `const __vtype presistent_basic_segment_tree<__s, __vtype, __calc>::inver_query(__id_type __id, __id_type __ver_from)`
> 
> `const __vtype presistent_basic_segment_tree<__s, __vtype, __calc>::inver_query(__id_type __lp, __id_type __rp, __id_type __ver_from)`

方法与对应的功能类似，只不过是在一个版本内进行修改，并不进行版本复制。

#### class presistent_segment_tree | oitl/assets/presistent_segment_tree.hpp
就是支持了区间修改的线段树可持久化。类似。

#### class chairman_tree | oitl/assets/presistent_segment_tree.hpp
你们要的主席树！

定义：`template<int __s, typename __vtype> class chairman_tree`

- `int __s`：区间大小。
- `typename __vtype`：存储类型，必须是数。

方法：

> `chairman_tree<__s, __vtype>::chairman_tree()`

构造一个长度为 `__s`，初始值为 `__vtype()` 的区间。

> `chairman_tree<__s, __vtype>::chairman_tree(__vtype *arr)`

将 `arr` 中的值复制到主席树内，并且通过 `min` 运算建树。

> `void charirman_tree<__s, __vtype>::rebuild(__vtype *arr)`

同上。

> `__vtype chairman_tree<__s, __vtype>::nth_number(__id_type __lp, __id_type __rp, __id_type __rk)`

求出从 `__lp` 到 `__rp` 里的第 `__rk` 大。

### oitl/sparse_table

稀疏表（ST 表），一种高效的 RMQ 实现方案。

#### class sparse_table | oitl/assets/sparse_table.hpp

定义：`template<int __s, typename __vtype, typename __calc> class sparse_table`

- `int __s`：区间大小
- `typename __vtype`：存储值
- `typename __calc`：区间运算类型

#### class dynamic_graph/graph/static_graph | oitl/assets/graph.hpp

定义：

- `template<dir is_directed, typename val_t> class dynamic_graph`
- `template<int n, dir is_directed, typename val_t> class graph`
- `template<int n, int m, dir is_directed, typename val_t> class static_graph`

这三个类型的方法类似，只不过内存处理方式不同。

- `dynamic_graph` 是点数不固定，边数不固定的空间分配方案。
- `graph` 是点数固定，边数不固定的空间分配方案。
- `static_graph` 是点数固定，边数也固定的空间分配方案。

（这里的固定是指有上限）

##### 不同的方法

###### 对于 `dynamic_graph`

> `void dynamic_graph<is_directed, val_t>::add_vertex()`

添加一个节点。

> `void dynamic_graph<is_directed, val_t>::set_vertex(__id_type __id_cnt)`

设置节点数，若不足则添加，否则保留前 `id_cnt` 个。

> `void dynamic_graph<is_directed, val_t>::clear_all()`

清除所有边和节点。

###### 对于有向图

> `bool is_connected(__id_type __ida, __id_type __idb)`

检测是否有从 `__ida` 号点到 `__idb` 号点是否有通路。

> `bool is_strongly_connected(__id_type __ida, __id_type __idb)`

检测从 `__ida` 到 `__idb` 是否有双向通路。

> `bool is_connected()`

检测整张图是否强连通，即任意两点之间都有双向通路。

> `__id_type scc_count()`

计算整张图的强连通分量数量。

> `void compress()`

强连通分量缩点。

###### 对于无向图

> `bool is_connected(__id_type __ida, __id_type __idb)`

检测

> `bool is_connected()`

检测整张图是否连通。

##### 相同的方法

> `void add_edge(__id_type __s, __id_type __t, val_t __v)`

加入一条从 `__s` 到 `__t` 的值为 `__v` 的边，若是无向图则加入无向边。

> `void clear()`

清除所有边。

> `iterator begin(__id_type __id)`

返回指向从 `__id` 号点出发的第一条边的迭代器。

> `iterator end(__id_type __id)`

返回指向从 `__id` 号点出发的末尾迭代器。

## English | 英语版

征求翻译……