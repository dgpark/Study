#include <stdio.h>
#include <vector>

using namespace std;


int main(void)
{
    int n, targetK;
    int coinType[100], numOfUse[10001];

    scanf("%d %d", &n, &targetK);

    // �ʱ�ȭ
    numOfUse[0] = 0;
    for (int i = 1; i <= targetK; ++i) {
        numOfUse[i] = 10001;
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d", &coinType[i]);
    }

    for (int i = 0; i < n; ++i) {
        for (int j = coinType[i]; j <= targetK; ++j) {
            if (numOfUse[j] > numOfUse[j - coinType[i]]) {
                numOfUse[j] = numOfUse[j - coinType[i]] + 1;
            }
        }
    }

    if (numOfUse[targetK] == 10001) {
        printf("%d", -1);
    }
    else {
        printf("%d", numOfUse[targetK]);
    }

    return 0;
}

// �����ʹ� ������������ �־����ٰ� �����ϰ� Ǯ��.

// dp���. branch & bound�� ����� dfs���� �Ʒ� dp�� �ð�ȿ����.
// ���� �迭 ���ں� �ּ� ��� ������ targetK�� �ִ�(10,000) + 1�� �ʱ�ȭ.
// �ּҰ��� �������� target������ �ּ� ��� ���� ����
// ������(numOfUse[j]) > numOfUse[j - coinType[i]]�� ��� numOfUse[j] = numOfUse[j - coinType[i]] + 1�� ����

//https://www.acmicpc.net/problem/2294