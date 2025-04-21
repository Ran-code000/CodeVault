# 并查集路径压缩细节，dfs细节思考

正确写法

```cpp
int find(int root){
  if(parents[root] != root){
      parents[root] = find(parents[root]);
  }
  return parents[root];
}
```

错误写法

```cpp
int find(int root){
  if(parents[root] != root){
      parents[root] = find(parents[root]);
  }
  else
  {
    return parents[root];
  }
}
```

## 反思

**错误原因：第二段代码路径压缩失效**

    1. 当 parents[root] == root 时，直接返回 parents[root]，因为本来就相等，所以这里不存在路径压缩

    2. 此时返回上一层调用时（执行完 find(parents[root]) ），发现此时直接返回了，没有返回值，为什么呢？
    
    3. 因为 return parents[root]; 在 else 语句， if 和 else 必只有一个成立

    4. 所以路径压缩失效 

