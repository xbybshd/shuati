# map和set不允许修改key  
set不允许修改key是通过把迭代器设为const，map不允许修改是把map的value类型设为pair<const K,V>