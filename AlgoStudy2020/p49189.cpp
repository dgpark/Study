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
            if (cost[nextNode] < 0) { // �湮 üũ. cost�迭�� -1�� �ʱ�ȭ �Ǿ�����.
                q.push(nextNode);
                cost[nextNode] = cost[startNode] + 1;
            }
        }
    }
    return cost[startNode];
}

int solution(int n, vector<vector<int>> edge) {
    int answer = 0, max = -1;

    //cost �ʱ�ȭ
    int cost[n + 1];
    fill_n(cost, n + 1, -1);
    
    //Edge E �ʱ�ȭ
    vector<vector<int>> E;
    E.resize(n + 1);
    
    //Edge E �Է�
    for (vector<int> input : edge) {
        E[input[0]].push_back(input[1]);
        E[input[1]].push_back(input[0]);
    }

    //bfs
    max = bfs(1, E, cost);
    
    //answer Ȯ��
    for (int i = 1; i <= n; ++i) {
        if (cost[i] == max) answer++;
    }

    return answer;
}

// vector Edge(int, int)������ �Է�
// Edge[1]���� �����Ͽ� ����� ��� queue�� push. (Edge[N����])
// Edge X�� �����ϴ� �ּ� ����� cost[X]�� ����.
// (��, cost[X]�� ���� -1�� ��쿡 ����. ��, ���� �湮 ���� ����϶�)
// https://programmers.co.kr/learn/courses/30/lessons/49189