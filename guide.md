# OITL 使用指南
这里介绍了 OITL 各个东西的使用指南。
## 树状数组
简单易懂，支持单点修改，区间查询。
### binary_indexed_tree
最基本的树状数组。支持单点修改和区间询问。

定义：`template<int _N, class _Val_t, class _Op> class binary_indexed_tree`。

- `int _N`：区间大小；
- `class _Val_t`：存储数据类型；
- `class _Op`：支持的运算。（树状数组支持满足结合律的运算）

### 类型
`binary_indexed_tree<_N, _Val_t, _Op>::value_type`：存储类型（aka. `_Val_t`）；

`binary_indexed_tree<_N, _Val_t, _Op>::operate_type`：运算类型（aka. `_Op`）。
### 成员函数
#### binary_indexex_tree
定义：`binary_indexed_tree<_N, _Val_t, _Op>::binary_indexed_tree(value_type identity)`（构造函数）。

可以构造一个元素均为 `identity` 初始的树状数组。

参数：

- `value_type identity`：即单位元。

无返回值。
#### modify
定义：`void binary_indexed_tree<_N, _Val_t, _Op>::modify(int ptr, value_type val)`。

进行单点修改，在 `ptr` 的位置上 _加上_ `val`。

参数：

- `int ptr`：位置指针（从 0 开始）；
- `value_type val`：修改值。

无返回值。
#### query
定义：`value_type binary_indexed_tree<_N, _Val_t, _Op>::query(int qr)`。

区间询问 [0,qr] 的值的 _和_。

参数：

- `int qr`：位置指针（从 0 开始）。

返回值：询问答案。
## 并查集
就是简单的并查集，支持快速的合并集合和询问集合。
### disjoint_set_union
最基本的并查集，可以完成所有基本并查集的功能。

定义：`class disjoint_set_union`。
### 成员函数
#### disjoint_set_union
定义：`disjoint_set_union::disjoint_set_union(int size = 0)`（构造函数）。

构造一个大小为 `size` 的并查集。

参数：

- `int size`：并查集初始大小。

无返回值。
#### empty
定义：`bool disjoint_set_union::empty() const`。

询问并查集内是否为空。

无参数。

返回值：如果为空，返回 `true`，否则为 `false`。
#### size
定义：`int disjoint_set_union::size() const`。

询问并查集的大小。

无参数。

返回值：并查集的大小。
#### clear
定义：`void disjoint_set_union::clear()`。

删除并查集内所有元素。

无参数，无返回值。
#### reset
定义：`void disjoint_set_union::reset()`。

重设并查集内所有元素，即将所有元素分离。

无参数，无返回值。
#### resize
定义：`void disjoint_set_union::resize(int size)`。

重新设置并查集大小。

如果输入值比原来大小更大，那么就新插入节点直到大小相同。

否则，删除多余的节点。**不保证不会运行时错误，请谨慎使用。**

参数：

- `int size`：重设后的并查集大小。

无返回值。
#### add_element
定义：`int disjoint_set_union::add_element()`。

插入一个新的并查集元素。

无参数。

返回值：新的元素的编号。（下标从 0 开始，下同）
#### unite
定义：`void disjoint_set_union::unite(int a, int b)`。

将 `a` 和 `b` 分别所在的集合合并。

参数：

- `int a`：第一个元素；
- `int b`：第二个元素。

无返回值。
#### same_set
定义：`bool disjoint_set_union::same_set(int a, int b)`。

查询 `a` 和 `b` 是否在一个集合内。

参数：

- `int a`：第一个元素；
- `int b`：第二个元素。

无返回值。
# Guides for OITL classes and functions