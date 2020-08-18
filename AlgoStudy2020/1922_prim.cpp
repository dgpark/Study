#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int nVertex, nEdge, minCost = 0;
int departure, destination, cost;
bool visited[1001];
vector<vector<pair<int, int>>> Edge; //Edge[start] = <cost, end> ������ �Է�. priority_queue�� ������ ����
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void prim(int vertex);

int main(void) {

	scanf("%d %d", &nVertex, &nEdge);

	Edge.resize(nVertex + 1); //0~nEdge-1���� ����Ƿ� +1���Ͽ� Edge[1]~Edge[nVertex]�� ������ ������ش�.

	for (int i = 0; i < nEdge; ++i) { //vertex�� ����
		scanf("%d %d %d", &departure, &destination, &cost);
		Edge[departure].push_back({ cost, destination });
		Edge[destination].push_back({ cost, departure });
	}

	prim(1);

	printf("%d", minCost);

	return 0;
}

void prim(int vertex) {
	visited[vertex] = true;

	for (auto costDesti : Edge[vertex]) { //�켱����ť�� cost�� ������ push.
		if (!visited[costDesti.second]) {
			pq.push({ costDesti.first, costDesti.second });
		}
	}

	while (!pq.empty()) {
		auto costDesti = pq.top(); //���� �湮���� ���� ���� �߿��� ���� cost�� ���� �������� pop�ȴ�.
		pq.pop();
		if (!visited[costDesti.second]) { //pop�� �������� �湮���� ���� ��� cost �߰�
			minCost += costDesti.first;
			prim(costDesti.second);
			return;
		}
	}
}

/*
������ ������ ���� ������ Prim �˰��� ���(Kruskal�� ������ ���Ŀ� �ð��� �����ɸ�)
Prim : O(ElogV), Kruskal : O(ElogE)

1. Vertex, Edge�� ���� �Է� //int
2. Edge �Է� �� ����// vector<vector<pair<int,int>>> edge
3. prim�˰��� ����.

4.vertex�� ��ȣ�� ���� prim�˰���
-> �ش� vertex �湮ó�� & Edge[vertex]�� �������� �湮���� ���� ��� edge[vertex]�� pair�� priority queue�� ��� ����.
-> priority queue�� empty�� �ƴϸ� �Ʒ� �ൿ �ݺ�
//priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq

1) pq.top �湮���� Ȯ��.(pop)
2) �湮 ������ continue
3) �湮 �������� ����ġ �߰� �� prim(pq.top�� second value) ���ȣ��
& return;
 */