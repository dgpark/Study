#include <stdio.h>

int Find(int x, int(&parent)[101]);
void Union(int x, int y, int(&parent)[101]);

int main(void) {
	int parent[101], inputNum[2];
	int computerNum, edgeNum, count = 0;
	scanf("%d %d", &computerNum, &edgeNum);

	for (int i = 0; i < computerNum + 1; i++) {
		parent[i] = i;
	}

	for (int i = 0; i < edgeNum; i++) {
		scanf("%d %d", &inputNum[0], &inputNum[1]);
		Union(inputNum[0], inputNum[1], parent);
	}

	for (int i = 2; i < computerNum + 1; i++) {
		if (Find(i, parent) == Find(1, parent)) {
			count++;
		}
	}

	printf("%d", count);

	return 0;
}

int Find(int x, int(&parent)[101]) {
	if (parent[x] == x) {  //parent[x]==x이면 초기화값.
		return parent[x];
	}
	return parent[x] = Find(parent[x], parent);
}

void Union(int x, int y, int(&parent)[101]) {
	int xParent = Find(x, parent);
	int yParent = Find(y, parent);
	if (xParent != yParent) {
		parent[yParent] = xParent;
	}
	return;
}


//입력조건
// 첫번째줄 컴퓨터 숫자 computerNum입력. computerNum은 항상 100 이하이므로 int parent[101]; 생성
// 두번째줄 네트워크 연결 Edge의 수 입력. edgeNum만큼 for문 반복.

//풀이
//Union Find 이용. x번 컴퓨터의 Find(x)가 == Find(1)이면 count++;
//Edge 수만큼 for문 반복하며 Union(x,y) 실행
//Union함수 내에서 x,y의 root를 찾아 parent[y의 루트] = x의 루트 연결

//int parent[100],int computerNum, int edgeNum; 함수 Union, 함수 Find 이용.


