#include <stdio.h>
#include <queue>

#define MAX_SIZE 100000

using namespace std;

bool visited[100001];

int main(void)
{
    int pointN, targetK, tempPoint, tempCount, count = 0;
    queue<pair<int, int>> moving; // {point, count}

    scanf("%d %d", &pointN, &targetK);

    if (targetK - pointN < 0) { // targetK가 pointN보다 작은수에 있을 때 (*2, +1 필요없음)
        tempPoint = pointN;
        while (tempPoint != targetK) {
            tempPoint--;
            count++;
        }
    }
    else {
        moving.push({ pointN, 0 });
        visited[pointN] = true;
        while (moving.front().first != targetK) { //pointN == targetK
            tempPoint = moving.front().first;
            tempCount = moving.front().second;
            moving.pop();

            // case x*2
            if (tempPoint * 2 == targetK) {
                count = tempCount + 1;
                break;
            }
            else if (tempPoint * 2 <= MAX_SIZE && !visited[tempPoint * 2]) {
                moving.push({ tempPoint * 2, tempCount + 1 });
                visited[tempPoint * 2] = true;
            }
            // case x+1
            if (tempPoint + 1 == targetK) {
                count = tempCount + 1;
                break;
            }
            else if (tempPoint + 1 <= MAX_SIZE && !visited[tempPoint + 1]) { // tempPoint+1 == targetK
                moving.push({ tempPoint + 1, tempCount + 1 });
                visited[tempPoint + 1] = true;
            }
            // case x-1
            if (tempPoint - 1 == targetK) {
                count = tempCount + 1;
                break;
            }
            else if (tempPoint - 1 >= 0 && !visited[tempPoint - 1]) { // tempPoint-1 == targetK
                moving.push({ tempPoint - 1, tempCount + 1 });
                visited[tempPoint - 1] = true;
            }
        }
    }
    printf("%d", count);
    return 0;
}

// 가장빠른, -> dp(x) or bfs. dp는 +1,-1할때마다 2배가 가능해서 너무 많아짐
// bfs. K-N < 0 이면 -1만한다.(2배는 양수로만 커짐)
// K-N >0 일때 bfs *2, -1, +1 순으로, queue에 넣는 bfs
// while문에서 *2, +1, -1단계별로 queue에 push
//https://www.acmicpc.net/problem/1697