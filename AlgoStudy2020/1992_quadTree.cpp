#include <iostream>
#include <vector>
#include <string>

using namespace std;

void quadTree(int(*matrix)[64], int N, int startRow, int startCol) {
	//분기여부 확인
	int firstElement = matrix[startRow][startCol];
	bool branching = false;

	for (int i = startRow; i < startRow + N; ++i) {
		for (int j = startCol; j < startCol + N; ++j) {
			if (matrix[i][j] != firstElement) {
				branching = true;
				break;
			}
		}
		if (branching == true)
			break;
	}
	if (branching == false) {
		//모두 같은 N*N행렬인 경우
		printf("%d", firstElement);
	}
	else {
		printf("(");
		//왼위
		quadTree(matrix, N / 2, startRow, startCol);
		//오위
		quadTree(matrix, N / 2, startRow, startCol + N / 2);
		//왼아
		quadTree(matrix, N / 2, startRow + N / 2, startCol);
		//오아
		quadTree(matrix, N / 2, startRow + N / 2, startCol + N / 2);
		printf(")");
	}
	return;
}

int main(void) {
	int matrix[64][64];
	string line;
	int N;

	cin >> N;

	for (int i = 0; i < N; ++i) {
		cin >> line;

		for (int j = 0; j < N; ++j) {
			matrix[i][j] = line[j] - '0';
		}
	}

	quadTree(matrix, N, 0, 0);

	return 0;
}

/*
NxN 행렬 입력 ( 이차원 배열 사용. matrix[64][64])

NxN 행렬이 1/4 구역씩 나뉘어지면서 1과 0을 판별한다. 괄호 연다.
-> 첫번째 원소가 나머지와 다 같으면 0 or 1 출력후 return.
-> 첫번째 원소와 다른 원소가 다르면 quadTree 재귀호출(왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래)
-> 괄호 닫는다.

-> 재귀호출 함수로 처리.

*/