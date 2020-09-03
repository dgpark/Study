#include <string>
#include <vector>
#include <queue>

using namespace std;

int bfs(const int& start, const vector<vector<int>>& E, int* cost) {
    queue<int> q;
    q.push(start);
    cost[start] = 0;

    int startNode;
    while (!q.empty()) {
        startNode = q.front();
        q.pop();

        for (int nextNode : E[startNode]) {
            if (cost[nextNode] < 0) { // 방문 체크. cost배열은 -1로 초기화 되어있음.
                q.push(nextNode);
                cost[nextNode] = cost[startNode] + 1;
            }
        }
    }
    return cost[startNode];
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0, max = -1;

    //cost 초기화
    int cost[n + 1];
    fill_n(cost, n + 1, -1);
    
    //Edge E 초기화
    vector<vector<int>> E;
    E.resize(n + 1);
    
    //Edge E 입력
    for (vector<int> input : edge) {
        E[input[0]].push_back(input[1]);
        E[input[1]].push_back(input[0]);
    }

    //bfs
    max = bfs(1, E, cost);
    
    //answer 확인
    for (int i = 1; i <= n; ++i) {
        if (cost[i] == max) answer++;
    }

    return answer;
}

// vector Edge(int, int)형으로 입력
// Edge[1]부터 시작하여 연결된 노드 queue에 push. (Edge[N까지])
// Edge X에 도달하는 최소 비용을 cost[X]에 저장.
// (단, cost[X]의 값이 -1인 경우에 갱신. 즉, 아직 방문 안한 노드일때)
// https://programmers.co.kr/learn/courses/30/lessons/49189