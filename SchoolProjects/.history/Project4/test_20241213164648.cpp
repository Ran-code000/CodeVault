void init()
{
  // ...省略部分已有代码...

  for (int i = 0; i < 33; i++)
  {
    int u = i + 1;            // 假设 u 是编号
    int v = (i + 1) % 33 + 1; // 假设 v 是下一个省份
    int w = 1;                // 假设 w 是边的权重

    graph.addEdge(u, v, w); // 添加边
  }
}
