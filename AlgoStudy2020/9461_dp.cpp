/*
//Simple Answer
#include <cstdio>
long long T, n, d[105]={0,1,1,1,2};
int main() {
    for(int i=5; i<= 100; i++) d[i] = d[i-1] + d[i-5]; // ���� 101�� �迭�� �̸� ����� �� ���س��� �����ϴ� ����. 
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
    long long num[5] = { 1,1,1,2,2 }; //�迭 ���̸� �ٿ������� 5���� �Ҵ��� ��.(+ ������ �ִ� ���̸� �� �� ���� �� ��� ����) �뷫 40B ����. (num[101]�� 808B ����) 
    int dpNum = 0;
    if (N == 0) {
        printf("0\n");
        return;
    }
    if (N < 6) {
        printf("%lld\n", num[N - 1]);
        return;
    }
    // �ĵ��� ������ ã�ƺ��� F(n) = F(n-2) + F(n-3)�̾���..
    // ���� 9461�� ������ ���� ã�Ҵ� ��Ģ�� F(n) = F(n-1) + F(n-5)
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

// ���� ���� : �޸𸮸� �� 800B ���̱� ���� �� ġ��� �ڵ尡 �ټ� ����� �������� ���δ�.
// �̷� ��쿡�� �޸� ���̰� ũ�� ������ �ܼ��ϰ� �ڵ带 ¥�°� ���� �� ����.