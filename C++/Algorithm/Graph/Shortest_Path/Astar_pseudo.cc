function A*(start,goal) 
	closedset := the empty set //已经被估算的节点集合 
	openset := set containing the initial node //将要被估算的节点集合 
	came_from := empty 
	map g_score[start] := 0 //g(n) 
	h_score[start] := heuristic_estimate_of_distance(start, goal) //h(n) 
	f_score[start] := h_score[start] //f(n)=h(n)+g(n)，由于g(n)=0，所以…… 
	while openset is not empty //当将被估算的节点存在时，执行 
		x := the node in openset having the lowest f_score[] value //取x为将被估算的节点中f(x)最小的 
		if x = goal //若x为终点，执行 
			return reconstruct_path(came_from,goal) //返回到x的最佳路径 
		remove x from openset //将x节点从将被估算的节点中删除 
		add x to closedset //将x节点插入已经被估算的节点 
		foreach y in neighbor_nodes(x) //对于节点x附近的任意节点y，执行 
			if y in closedset //若y已被估值，跳过 
				continue 
			tentative_g_score := g_score[x] + dist_between(x,y) //从起点到节点y的距离

			if y not in openset //若y不是将被估算的节点 
				add y to openset //将y插入将被估算的节点中 
				tentative_is_better := true 

			else if tentative_g_score < g_score[y] //如果y的估值小于y的实际距离 
				tentative_is_better := true //暂时判断为更好 
			else 
				tentative_is_better := false //否则判断为更差 
			if tentative_is_better = true //如果判断为更好 
				came_from[y] := x //将y设为x的子节点 
				g_score[y] := tentative_g_score 
				h_score[y] := heuristic_estimate_of_distance(y, goal) 
				f_score[y] := g_score[y] + h_score[y] 
	return failure 
function reconstruct_path(came_from,current_node) 
	if came_from[current_node] is set 
		p = reconstruct_path(came_from,came_from[current_node]) 
		return (p + current_node) 
	else
		return current_node 

A*搜索算法，俗称A星算法。这是一种在图形平面上，有多个节点的路径，求出最低通过成本的算法。常用于游戏中的NPC的移动计算，或在线游戏的BOT的移动计算上。
该算法综合了Best-First Search和Dijkstra算法的优点：在进行启发式搜索提高算法效率的同时，可以保证找到一条最优路径（基于评估函数）。
在此算法中，如果以 g(n)表示从起点到任意顶点n的实际距离，h(n)表示任意顶点n到目标顶点的估算距离（根据所采用的评估函数的不同而变化），那么 A*算法的估算函数为：
f(n)=g(n)+h(n)
这个公式遵循以下特性：
如果g(n)为0，即只计算任意顶点n到目标的评估函数h(n)，而不计算起点到顶点n的距离，则算法转化为使用贪心策略的Best-First Search，速度最快，但可能得不出最优解；
如果h(n)不为0，则一定可以求出最优解，而且h(n)越小，需要计算的节点越多，算法效率越低，常见的评估函数有——欧几里得距离、曼哈顿距离、切比雪夫距离；
如果h(n)为0，即只需求出起点到任意顶点n的最短路径g(n)，而不计算任何评估函数h(n)，则转化为单源最短路径问题，即Dijkstra算法，此时需要计算最多的定点；
