#include <iostream>
#include <string>
#include <queue>

using namespace std;

int N, M;
int map[100][100]; // N번째 행 or M번째 열에서 방향 탐색시 N+1, M+1 이 탐색되기 때문에 101까지 범위 지정.
bool visited[100][100];
int const direction[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; //상 하 좌 우

int BFS();

int main(void) {
    string strInput;
    scanf("%d %d", &N, &M);

    for (int y = 0; y < N; y++) {
        cin >> strInput;
        for (int x = 0; x < M; x++) {
            map[y][x] = strInput.at(x) - 48;
        }
    }

    cout << BFS();

    return 0;
}

int BFS() {
    queue <pair<pair<int, int>, int>> q; // (y, x, minimum_distance)
    q.push(make_pair(make_pair(0, 0), 1));
    visited[0][0] = true;

    while (!q.empty()) {
        int y = q.front().first.first;
        int x = q.front().first.second;
        int minDistance = q.front().second;

        if (y == N - 1 && x == M - 1) {
            return minDistance; // answer point.
        }

        q.pop();

        for (int i = 0; i < 4; i++) {
            int yNext = y + direction[i][0];
            int xNext = x + direction[i][1];

            if (yNext >= 0 && yNext < N && xNext >= 0 && xNext < M) { // if문에서 100*100을 벗어나면(ex : 101) 자체적으로 거르기 때문에 처음에 map[100][100]으로 선언.
                if (map[yNext][xNext] && !visited[yNext][xNext]) {
                    visited[yNext][xNext] = true;
                    q.push(make_pair(make_pair(yNext, xNext), minDistance + 1));
                }
            }
        }
    }

    return -1; // should not be called.
}
