#include <iostream>
using namespace std;

const int maxnum = 100;       // 最大顶点数
const int maxint = 999999;    // ∞可用最大值代替

// 各数组从下标1开始
int dist[maxnum];            // 表示当前点到源点的最短路径长度
int pre[maxnum];             // 记录当前点的前一个结点
int arcs[maxnum][maxnum];    // 记录图的两点间路径长度
int n, m;                    // 图的结点数和路径数

// 迪杰斯特拉算法
void Dijkstra(int n, int v, int *dist, int *pre, int arcs[maxnum][maxnum]){

	//第一部分：初始化
	int i;
	bool S[maxnum];                      // 判断是否该点已存入到S集合中,存入为1、未存入为0
	for (i = 1; i <= n; i++){
		dist[i] = arcs[v][i];            // arcs[v][i]记录路径长度的数组
		S[i] = 0;                        // 初始都未用过该点
		if (dist[i] == maxint)           // 当1指向的目标路径没有直接路径的时候（路径长度数值无限大）		
			pre[i] = 0;
		else
			pre[i] = v;
	}
	S[1] = 1;

	// 第二部分，循环查找结点 
	// 从第二个节点开始，第一个为源点
	for (i = 2; i <= n; i++){
		int j;
		int w;                          // 用于记录当前距离值最小的终点
		int min = maxint;
		// 找出当前未使用结点j的dist[j]最小值
		for (j = 2; j <= n; j++){
			if ((!S[j]) && dist[j] < min){
				min = dist[j];
				w = j;
			}
		}
		S[w] = 1;

		// 更新dist
		for (j = 2; j <= n; j++){
			//如果从最短路径开始有到达循环目标的结点，进行如下判断
			if ((!S[j]) && arcs[w][j] < maxint){
				int newdist = dist[w] + arcs[w][j];
				if (newdist < dist[j]){
					dist[j] = newdist;
					pre[j] = w;
				}
			}
		}
	}
}

// 查找从源点v到终点的路径并输出
void searchPath(int *pre, int v, int w){
	//判断有无路径到达
	if (dist[w] == 999999){
		cout<<"无路径到达！\n";
	}
	else{
		int que[maxnum];                 // 创建数组便于输出
		int tot = 1;                     // 记录数组返回位置 
		que[tot] = w;
		int tmp = pre[w];                // tmp用于记录当前最短路径结点的前一个结点
		tot++;
		//当前最短路径结点的前一个结点不为1
		while (tmp != v){
			que[tot] = tmp;
			tmp = pre[tmp];
			tot++;
		}
		que[tot] = v;
		for (int i = tot; i >= 1; i--)
		if (i != 1)
			cout << que[i] << " -> ";
		else
			cout << que[i] << endl;
	}
}

int main(){
	int i, j;
	cout << "输入结点数\n";
	cin >> n;
	cout << "输入路径数\n";
	cin >> m;
	int p, q, len;                       // p、q两点及其路径长度len

	// 初始化arcs为maxint
	for (i = 1; i <= n; i++)
	for (j = 1; j <= n; j++)
		arcs[i][j] = maxint;
	cout << "请输入所有相关的路径信息 格式；开始节点 指向节点 路径长度\n";
	for (i = 1; i <= m; i++){
		cout << "请输入第" << i << "条路径的信息";
		cin >> p >> q >> len;
		if (len < arcs[p][q]){
			arcs[p][q] = len;
		}
	}

	// 初始化最短路径长度
	for (i = 1; i <= n; i++)
		dist[i] = maxint;                // 初始每个边长都为无限

	// 打印邻接矩阵
	for (i = 1; i <= n; i++){
		for (j = 1; j <= n; j++)
			printf("%8d", arcs[i][j]);
		cout<<endl;
	}
	cout<<endl;

	// 求最短路径长度
	Dijkstra(n, 1, dist, pre, arcs);
	for (i = 2; i <= n; i++){
		cout << "源点到第" << i << "个顶点的最短路径长度: " << dist[i] << endl;
		cout << "源点到其的路径为: ";
		searchPath(pre, 1, i);
	}

	system("pause");
	return 0;
}