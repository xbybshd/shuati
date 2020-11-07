### map和set不允许修改key  
set不允许修改key是通过把迭代器设为const，map不允许修改是把map的value类型设为pair<const K,V>

### std::tie：创建左值引用的 tuple，或将 tuple 解包为独立对象
```cpp
float alpha;
float beta;
float gamma;
std::tie(alpha, beta, gamma) = tup;
auto [a,b,c]=tup;
```

### c++ tuple使用  
初始化
```
tuple<int,int,int> a(1,2,3);
auto itme=make_tuple("string",3,20.01);
```