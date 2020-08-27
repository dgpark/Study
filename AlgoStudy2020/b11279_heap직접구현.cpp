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
	//heap의 마지막에 inputNum 추가
	heapList[++countHeap] = inputNum;

	//child와 parent 비교하며 child가 클 경우 위로 올리기
	int child = countHeap;
	int parent = child / 2;
	while (child > 1 && heapList[parent] < heapList[child]) {
		swap(&heapList[parent], &heapList[child]);
		child = parent;
		parent = child / 2;
	}
}

int Heap::pop() {
	// pop할 number 저장후 해당 자리에 heap의 마지막 데이터 이동
	int popNum = heapList[1];
	heapList[1] = heapList[countHeap];
	heapList[countHeap--] = 0;

	// child와 parent 비교하며 parent가 작을 경우 아래로 내리기 
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



// 첫째줄 N만큼 정수 입력. (자연수 -> heap에 추가 / 0 -> heap의 최대값 pop)
// main의 for문에서 값 입력 -> if문으로 0보다 크면 heap에 추가, 0이면 heap에서 삭제 (heap에 데이터가 없을 경우 0 출력)
// heap에서 push와 pop, swap, empty, top 함수 필요. -> 클래스로 묶기.