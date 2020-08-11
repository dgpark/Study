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

//ù°�� �Է¼��� N ����.
//priority queue�� N���� ���� �Է¹���
//�ڿ����� push, 0�̸� pop(���� ���� ������, greater<int>), ��������� 0�Է½� 0 ���)