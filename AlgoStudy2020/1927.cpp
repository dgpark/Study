#include <stdio.h>
#include <queue>

using namespace std;

int main(void) {
	priority_queue <int, vector<int>, greater<int> > pq;
	int N, inputNum, data;
	scanf("%d", &N);

	for (int i = 0; i < N; ++i) {
		scanf("%d", &inputNum);
		if (inputNum == 0) {
			if (!pq.empty()) {
				printf("%d\n", pq.top());
				pq.pop();
			}
			else {
				printf("0\n");
			}
		}
		else {
			pq.push(inputNum);
		}
	}

	return 0;
}

//첫째줄 입력숫자 N 읽음.
//priority queue에 N개의 숫자 입력받음
//자연수면 push, 0이면 pop(작은 숫자 순으로, greater<int>), 비어있을때 0입력시 0 출력)