#include <stdio.h>
#include <algorithm>
#include <queue>

using namespace std;

int main(void) {
	int N;
	int inputNum;
	priority_queue<int> maxHeap;

	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &inputNum);
		if (inputNum == 0) {
			printf("%d\n", maxHeap.empty() ? 0 : maxHeap.top());
			if (!maxHeap.empty()) {
				maxHeap.pop();
			}
		}
		else {
			maxHeap.push(inputNum);
		}
	}

	return 0;
}

// 첫째줄 N만큼 정수 입력. (자연수 -> heap에 추가 / 0 -> heap의 최대값 pop)
// main의 for문에서 값 입력 -> if문으로 0보다 크면 heap에 추가, 0이면 heap에서 삭제 (heap에 데이터가 없을 경우 0 출력)

