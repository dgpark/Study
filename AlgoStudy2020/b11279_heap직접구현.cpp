#include <stdio.h>

using namespace std;

class Heap {
private:
	int heapList[100001] = { 0, };
	int countHeap = 0;
public:
	void swap(int* a, int* b);
	void push(int inputNum);
	int pop();
	bool empty();
	int top();
};

void Heap::swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void Heap::push(int inputNum) {
	//heap�� �������� inputNum �߰�
	heapList[++countHeap] = inputNum;

	//child�� parent ���ϸ� child�� Ŭ ��� ���� �ø���
	int child = countHeap;
	int parent = child / 2;
	while (child > 1 && heapList[parent] < heapList[child]) {
		swap(&heapList[parent], &heapList[child]);
		child = parent;
		parent = child / 2;
	}
}

int Heap::pop() {
	// pop�� number ������ �ش� �ڸ��� heap�� ������ ������ �̵�
	int popNum = heapList[1];
	heapList[1] = heapList[countHeap];
	heapList[countHeap--] = 0;

	// child�� parent ���ϸ� parent�� ���� ��� �Ʒ��� ������ 
	int parent = 1;
	int child = parent * 2;
	while (child <= countHeap) {
		if (heapList[child] < heapList[parent] && heapList[child + 1] < heapList[parent]) {
			break;
		}
		else if (heapList[child] > heapList[child + 1]) {
			swap(&heapList[parent], &heapList[child]);
			parent = child;
			child = parent * 2;
		}
		else {
			swap(&heapList[parent], &heapList[child + 1]);
			parent = child + 1;
			child = parent * 2;
		}
	}
	return popNum;
}

bool Heap::empty() {
	if (heapList[1] == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Heap::top() {
	return heapList[1];
}

int main(void) {
	int N;
	int inputNum;

	scanf("%d", &N);
	Heap maxHeap;

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
// heap���� push�� pop, swap, empty, top �Լ� �ʿ�. -> Ŭ������ ����.