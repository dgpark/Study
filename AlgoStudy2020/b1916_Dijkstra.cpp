#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

bool visited[1001];

int main(void) {

	struct Edge {
		int end, cost;
		Edge(int end, int cost) : end(end), cost(cost) {}
	};

	int numOfCity, numOfBus, sfStart, sfEnd, sfCost, start, end;
	vector<Edge> routeEdge[1001];

	//�Է�
	scanf("%d %d", &numOfCity, &numOfBus);

	for (int i = 0; i < numOfBus; ++i) {
		scanf("%d %d %d", &sfStart, &sfEnd, &sfCost);
		routeEdge[sfStart].push_back(Edge(sfEnd, sfCost));
	}

	scanf("%d %d", &start, &end);

	// ���ͽ�Ʈ��
	// cost �ʱ�ȭ(inf�� = �־��� �������� ������ �ִ� cost + 1)
	int cost[1001];
	for (int i = 1; i < numOfCity + 1; ++i) {
		cost[i] = 100000001;
	}

	int city = start;
	cost[start] = 0;// �Է¹޾Ҵ� ���� �������� ���Ž�� ����.
	for (int i = 0; i < numOfCity; ++i) {
		visited[city] = true; // �湮ó��
		for (int j = 0; j < routeEdge[city].size(); ++j) {
			int toIndex = routeEdge[city][j].end;
			int newCost = cost[city] + routeEdge[city][j].cost;//���� city���� cost = ���� cost + ���ο� cost
			if (cost[toIndex] > newCost) // start�������� toindex������ �ּ� �Ÿ� ����
				cost[toIndex] = newCost; 
		}

		if (city == end) // ������������ �ּ� �Ÿ��� �������ٸ� �ݺ��� break
			break;

		int nextMin = 100000002;
		for (int j = 1; j < numOfCity + 1; ++j) {
			if (!visited[j] && cost[j] < nextMin) { // �ּ� ��� �������� �̵��� ���� ���ϱ�.
				nextMin = cost[j];
				city = j;
			}
		}
	}

	printf("%d", cost[end]);
	return 0;
}



/*
.���ͽ�Ʈ��

1. �Է� : int numOfCity, int numOfBus, vector<Edge> routeEdge, int start, int end;
//struct Edge �̿�.(bool operator �����)
2. ���ͽ�Ʈ�� �˰��� :
2-1)
int visited[1001];
int cost[1001]; //start ���ô� cost 0, visited[0] = true;
-> routeEdge[start]���� �����ؼ� �̾����� ������ ��� vertex�� ���� cost ������Ʈ
-> cost[end]�� �� ���
 */