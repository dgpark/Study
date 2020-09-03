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

    if (targetK - pointN < 0) { // targetK�� pointN���� �������� ���� �� (*2, +1 �ʿ����)
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

// �������, -> dp(x) or bfs. dp�� +1,-1�Ҷ����� 2�谡 �����ؼ� �ʹ� ������
// bfs. K-N < 0 �̸� -1���Ѵ�.(2��� ����θ� Ŀ��)
// K-N >0 �϶� bfs *2, -1, +1 ������, queue�� �ִ� bfs
// while������ *2, +1, -1�ܰ躰�� queue�� push
//https://www.acmicpc.net/problem/1697