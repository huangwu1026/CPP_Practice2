#include <iostream>
using namespace std;

const int maxnum = 100;       // ��󶥵���
const int maxint = 999999;    // �޿������ֵ����

// ��������±�1��ʼ
int dist[maxnum];            // ��ʾ��ǰ�㵽Դ������·������
int pre[maxnum];             // ��¼��ǰ���ǰһ�����
int arcs[maxnum][maxnum];    // ��¼ͼ�������·������
int n, m;                    // ͼ�Ľ������·����

// �Ͻ�˹�����㷨
void Dijkstra(int n, int v, int *dist, int *pre, int arcs[maxnum][maxnum]){

	//��һ���֣���ʼ��
	int i;
	bool S[maxnum];                      // �ж��Ƿ�õ��Ѵ��뵽S������,����Ϊ1��δ����Ϊ0
	for (i = 1; i <= n; i++){
		dist[i] = arcs[v][i];            // arcs[v][i]��¼·�����ȵ�����
		S[i] = 0;                        // ��ʼ��δ�ù��õ�
		if (dist[i] == maxint)           // ��1ָ���Ŀ��·��û��ֱ��·����ʱ��·��������ֵ���޴�		
			pre[i] = 0;
		else
			pre[i] = v;
	}
	S[1] = 1;

	// �ڶ����֣�ѭ�����ҽ�� 
	// �ӵڶ����ڵ㿪ʼ����һ��ΪԴ��
	for (i = 2; i <= n; i++){
		int j;
		int w;                          // ���ڼ�¼��ǰ����ֵ��С���յ�
		int min = maxint;
		// �ҳ���ǰδʹ�ý��j��dist[j]��Сֵ
		for (j = 2; j <= n; j++){
			if ((!S[j]) && dist[j] < min){
				min = dist[j];
				w = j;
			}
		}
		S[w] = 1;

		// ����dist
		for (j = 2; j <= n; j++){
			//��������·����ʼ�е���ѭ��Ŀ��Ľ�㣬���������ж�
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

// ���Ҵ�Դ��v���յ��·�������
void searchPath(int *pre, int v, int w){
	//�ж�����·������
	if (dist[w] == 999999){
		cout<<"��·�����\n";
	}
	else{
		int que[maxnum];                 // ��������������
		int tot = 1;                     // ��¼���鷵��λ�� 
		que[tot] = w;
		int tmp = pre[w];                // tmp���ڼ�¼��ǰ���·������ǰһ�����
		tot++;
		//��ǰ���·������ǰһ����㲻Ϊ1
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
	cout << "��������\n";
	cin >> n;
	cout << "����·����\n";
	cin >> m;
	int p, q, len;                       // p��q���㼰��·������len

	// ��ʼ��arcsΪmaxint
	for (i = 1; i <= n; i++)
	for (j = 1; j <= n; j++)
		arcs[i][j] = maxint;
	cout << "������������ص�·����Ϣ ��ʽ����ʼ�ڵ� ָ��ڵ� ·������\n";
	for (i = 1; i <= m; i++){
		cout << "�������" << i << "��·������Ϣ";
		cin >> p >> q >> len;
		if (len < arcs[p][q]){
			arcs[p][q] = len;
		}
	}

	// ��ʼ�����·������
	for (i = 1; i <= n; i++)
		dist[i] = maxint;                // ��ʼÿ���߳���Ϊ����

	// ��ӡ�ڽӾ���
	for (i = 1; i <= n; i++){
		for (j = 1; j <= n; j++)
			printf("%8d", arcs[i][j]);
		cout<<endl;
	}
	cout<<endl;

	// �����·������
	Dijkstra(n, 1, dist, pre, arcs);
	for (i = 2; i <= n; i++){
		cout << "Դ�㵽��" << i << "����������·������: " << dist[i] << endl;
		cout << "Դ�㵽���·��Ϊ: ";
		searchPath(pre, 1, i);
	}

	system("pause");
	return 0;
}