### 字符串，高级树，dp，数学，图论   

#### 回溯法  
如果不想再dfs外面再进行for循环遍历，把修改和恢复操作写在dfsfor循环里面比较好。  
纯网格搜索，可以把循环写外面，因为这是很明显的二维循环   

写排列和组合的一个区别就是，排列再中间元素时，也是需要从头开始搜索，因为前后位置颠倒也是排列   
组合只需要从头开始慢慢往后搜就行，后面不需要再搜索前面，因为前后位置颠倒元素一样被视作是同一个组合

#### 图论  
##### 拓扑排序  
bfs做法相当于按照入度为0遍历，最后有环的那个节点入度无法变为0，所以遍历不到。  
dfs相当于深搜遍历，节点分为当前遍历路径上，和已经完全遍历的其他路径，未遍历三种状态，如果在遍历的时候遇到状态1，那就说明有环。
当然写的时候可以把未遍历和dfs用 && 写在一起