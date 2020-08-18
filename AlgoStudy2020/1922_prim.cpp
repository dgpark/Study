#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

int nVertex, nEdge, minCost = 0;
int departure, destination, cost;
bool visited[1001];
vector<vector<pair<int, int>>> Edge; //Edge[start] = <cost, end> 순으로 입력. priority_queue의 정렬을 위해
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void prim(int vertex);

int main(void) {

	scanf("%d %d", &nVertex, &nEdge);

	Edge.resize(nVertex + 1); //0~nEdge-1까지 생기므로 +1을하여 Edge[1]~Edge[nVertex]의 공간을 만들어준다.

	for (int i = 0; i < nEdge; ++i) { //vertex간 연결
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

	for (auto costDesti : Edge[vertex]) { //우선순위큐에 cost와 목적지 push.
		if (!visited[costDesti.second]) {
			pq.push({ costDesti.first, costDesti.second });
		}
	}

	while (!pq.empty()) {
		auto costDesti = pq.top(); //현재 방문하지 않은 집합 중에서 가장 cost가 낮은 목적지가 pop된다.
		pq.pop();
		if (!visited[costDesti.second]) { //pop된 목적지가 방문하지 않은 경우 cost 추가
			minCost += costDesti.first;
			prim(costDesti.second);
			return;
		}
	}
}

/*
간선의 개수가 많기 때문에 Prim 알고리즘 사용(Kruskal은 간선의 정렬에 시간이 오래걸림)
Prim : O(ElogV), Kruskal : O(ElogE)

1. Vertex, Edge의 개수 입력 //int
2. Edge 입력 및 연결// vector<vector<pair<int,int>>> edge
3. prim알고리즘 시작.

4.vertex의 번호를 받은 prim알고리즘
-> 해당 vertex 방문처리 & Edge[vertex]의 목적지가 방문하지 않은 경우 edge[vertex]의 pair를 priority queue에 모두 저장.
-> priority queue가 empty가 아니면 아래 행동 반복
//priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq

1) pq.top 방문여부 확인.(pop)
2) 방문 했으면 continue
3) 방문 안했으면 가중치 추가 후 prim(pq.top의 second value) 재귀호출
& return;
 */