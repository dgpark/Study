/*
//Simple Answer
#include <cstdio>
long long T, n, d[105]={0,1,1,1,2};
int main() {
    for(int i=5; i<= 100; i++) d[i] = d[i-1] + d[i-5]; // 길이 101의 배열에 미리 결과를 다 구해놓고 시작하는 차이. 
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        printf("%lld\n", d[n]);
    }
    return 0;
}
*/

#include <cstdio>

using namespace std;

void PSequence(int N);

int main(void) {
    int T, testN;
    scanf("%d", &T);

    for (int i = 0; i < T; i++) {
        scanf("%d", &testN);
        PSequence(testN);
    }

    return 0;
}

void PSequence(int N) {
    long long num[5] = { 1,1,1,2,2 }; //배열 길이를 줄여보려고 5개만 할당해 봄.(+ 수열의 최대 길이를 알 수 없을 때 사용 가능) 대략 40B 차지. (num[101]은 808B 차지) 
    int dpNum = 0;
    if (N == 0) {
        printf("0\n");
        return;
    }
    if (N < 6) {
        printf("%lld\n", num[N - 1]);
        return;
    }
    // 파도바 수열을 찾아보니 F(n) = F(n-2) + F(n-3)이었음..
    // 내가 9461번 문제를 보고 찾았던 규칙은 F(n) = F(n-1) + F(n-5)
    for (int i = 0; i < (N - 5); i++) { 
        if (dpNum == 0) {
            num[dpNum] = num[4] + num[0];
        }
        else {
            num[dpNum] = num[dpNum - 1] + num[dpNum];
        }

        if (dpNum == 4) {
            dpNum = 0;
        }
        else {
            dpNum++;
        }
    }

    if (dpNum == 0) {
        printf("%lld\n", num[4]);
    }
    else {
        printf("%lld\n", num[dpNum - 1]);
    }

    return;
}

// 개인 생각 : 메모리를 약 800B 줄이기 위한 것 치고는 코드가 다소 길어져 너저분해 보인다.
// 이런 경우에는 메모리 차이가 크지 않으면 단순하게 코드를 짜는게 나을 것 같다.