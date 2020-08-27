#include <iostream>
#include <vector>
#include <string>

using namespace std;

void quadTree(int(*matrix)[64], int N, int startRow, int startCol) {
	//�б⿩�� Ȯ��
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
		//��� ���� N*N����� ���
		printf("%d", firstElement);
	}
	else {
		printf("(");
		//����
		quadTree(matrix, N / 2, startRow, startCol);
		//����
		quadTree(matrix, N / 2, startRow, startCol + N / 2);
		//�޾�
		quadTree(matrix, N / 2, startRow + N / 2, startCol);
		//����
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
NxN ��� �Է� ( ������ �迭 ���. matrix[64][64])

NxN ����� 1/4 ������ ���������鼭 1�� 0�� �Ǻ��Ѵ�. ��ȣ ����.
-> ù��° ���Ұ� �������� �� ������ 0 or 1 ����� return.
-> ù��° ���ҿ� �ٸ� ���Ұ� �ٸ��� quadTree ���ȣ��(������, ��������, ���ʾƷ�, �����ʾƷ�)
-> ��ȣ �ݴ´�.

-> ���ȣ�� �Լ��� ó��.

*/