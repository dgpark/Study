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

	//입력
	scanf("%d %d", &numOfCity, &numOfBus);

	for (int i = 0; i < numOfBus; ++i) {
		scanf("%d %d %d", &sfStart, &sfEnd, &sfCost);
		routeEdge[sfStart].push_back(Edge(sfEnd, sfCost));
	}

	scanf("%d %d", &start, &end);

	// 다익스트라
	// cost 초기화(inf값 = 주어진 문제에서 가능한 최대 cost + 1)
	int cost[1001];
	for (int i = 1; i < numOfCity + 1; ++i) {
		cost[i] = 100000001;
	}

	int city = start;
	cost[start] = 0;// 입력받았던 시작 지점에서 경로탐색 시작.
	for (int i = 0; i < numOfCity; ++i) {
		visited[city] = true; // 방문처리
		for (int j = 0; j < routeEdge[city].size(); ++j) {
			int toIndex = routeEdge[city][j].end;
			int newCost = cost[city] + routeEdge[city][j].cost;//다음 city로의 cost = 기존 cost + 새로운 cost
			if (cost[toIndex] > newCost) // start지점부터 toindex까지의 최소 거리 갱신
				cost[toIndex] = newCost; 
		}

		if (city == end) // 목적지까지의 최소 거리가 구해졌다면 반복문 break
			break;

		int nextMin = 100000002;
		for (int j = 1; j < numOfCity + 1; ++j) {
			if (!visited[j] && cost[j] < nextMin) { // 최소 비용 기준으로 이동할 도시 구하기.
				nextMin = cost[j];
				city = j;
			}
		}
	}

	printf("%d", cost[end]);
	return 0;
}



/*
.다익스트라

1. 입력 : int numOfCity, int numOfBus, vector<Edge> routeEdge, int start, int end;
//struct Edge 이용.(bool operator 만들기)
2. 다익스트라 알고리즘 :
2-1)
int visited[1001];
int cost[1001]; //start 도시는 cost 0, visited[0] = true;
-> routeEdge[start]에서 시작해서 이어지는 방향의 모든 vertex를 돌며 cost 업데이트
-> cost[end]의 값 출력
 */