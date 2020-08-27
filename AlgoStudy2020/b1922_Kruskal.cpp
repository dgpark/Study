#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
	int departure, destination, cost;
	bool operator < (const Edge& other) const {
		return cost < other.cost;
	}
};

int network[1001];

void MakeSet(const int& numOfVertex);
int Find(const int& x);
void Union(int x, int y);

int main(void) {
	int numOfVertex, numOfEdge, minCost = 0;
	Edge inputEdge;

	scanf("%d %d", &numOfVertex, &numOfEdge);

	vector<Edge> EdgeList(numOfEdge);

	for (int i = 0; i < numOfEdge; ++i) {
		scanf("%d %d %d", &EdgeList[i].departure, &EdgeList[i].destination, &EdgeList[i].cost);
	}
	sort(EdgeList.begin(), EdgeList.end());

	MakeSet(numOfVertex);

	for (int i = 0; i < numOfEdge; ++i) {
		Edge edge = EdgeList[i];
		int xParent = Find(edge.departure);
		int yParent = Find(edge.destination);
		if (xParent != yParent) {
			Union(edge.departure, edge.destination);
			minCost += edge.cost;
		}
	}

	printf("%d", minCost);

	return 0;
}

void MakeSet(const int& numOfVertex) {
	for (int i = 1; i < numOfVertex + 1; ++i) {
		network[i] = i;
	}
}

int Find(const int& x) {
	if (network[x] == x) {
		return x;
	}
	else {
		return network[x] = Find(network[x]);
	}
}

void Union(int x, int y) {
	x = Find(x);
	y = Find(y);
	network[x] = y;
}

/*
ũ�罺Į �˰��� ���
1. Vertex, Edge�� ���� �Է�
2. �� Edge ����. (�̹��� ����ü�ε� ������)
3. Edge�� cost�� �������� �������� sort
4. kruskal algorithm.
MakeSet, Find, Union
���ĵ� Edge�� �ϳ��� pop. -> Union-Find�� �̿�

 */