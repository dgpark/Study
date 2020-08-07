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

// ù°�� N��ŭ ���� �Է�. (�ڿ��� -> heap�� �߰� / 0 -> heap�� �ִ밪 pop)
// main�� for������ �� �Է� -> if������ 0���� ũ�� heap�� �߰�, 0�̸� heap���� ���� (heap�� �����Ͱ� ���� ��� 0 ���)

