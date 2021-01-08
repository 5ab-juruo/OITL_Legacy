# binary_indexed_tree
最基本的树状数组。支持单点修改和区间询问。

## 定义
> `template<int _N, class _Val_t, class _Op> class binary_indexed_tree`。

### 模板参数
- `int _N`：区间大小；
- `class _Val_t`：存储数据类型；
- `class _Op`：支持的运算。（树状数组支持满足结合律的运算）