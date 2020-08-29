#include <stdio.h>
#include <vector>

using namespace std;


int main(void)
{
    int n, targetK;
    int coinType[100], numOfUse[10001];

    scanf("%d %d", &n, &targetK);

    // 초기화
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

// 데이터는 오름차순으로 주어진다고 가정하고 풀이.

// dp사용. branch & bound를 사용한 dfs보다 아래 dp가 시간효율적.
// 숫자 배열 숫자별 최소 사용 갯수를 targetK의 최댓값(10,000) + 1로 초기화.
// 최소값인 동전으로 target값까지 최소 사용 갯수 갱신
// 기존값(numOfUse[j]) > numOfUse[j - coinType[i]]인 경우 numOfUse[j] = numOfUse[j - coinType[i]] + 1로 갱신

//https://www.acmicpc.net/problem/2294